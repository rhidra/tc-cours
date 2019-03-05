#include "hubert.h"

int id_file;
int id_shm;
int id_sem;
COURSIER coursiers[MAX_COURSIER];
COURSIER *shm;
RESTO restos[NB_RESTO];

int main() {
  srand(time(NULL));
  int i, pid;

  // Création des processus coursiers
  for (i = 0; i < MAX_COURSIER; i++) {
    pid = fork();
    if (pid == -1) {
      perror(RED "Erreur dans la création des coursiers !");
      exit(1);
    } else if (pid == 0)
    break;

    coursiers[i].pid_coursier = pid;
    coursiers[i].etat = 0;
  }

  if (pid == 0) {
    coursier();
  } else {
    printf(GRN "[HUBERT]" RESET "Démarrage du serveur Hubert ...\n");
    // Redirection des signaux
    signal(SIGINT, fin);
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);

    // Création de la file de messages
    key_t key = ftok("hubert.c", 0);
    id_file = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
    if (id_file == -1) {
      perror(RED "Erreur dans la création de la file de message !");
      exit(1);
    }

    // Création mémoire partagée
    id_shm = create_shmem(getpid(), MAX_COURSIER * sizeof(COURSIER));
    if (id_shm == -1) {
      perror(RED "Erreur dans la création de la mémoire partagée !");
      exit(1);
    }

    // Création sémaphore de la shm
    id_sem = create_semaphore(getpid());
    if (id_sem == -1) {
      perror(RED "Erreur dans la création de la sémaphore !");
      exit(1);
    }
    if (init_semaphore(id_sem, 0) == -1) {
      perror(RED "Erreur dans l'initialisation de la sémaphore !");
      exit(1);
    }

    hubert();
  }

  return 0;
}

void hubert() {
  int i;
  MSGBUF msg;

  // Initalisation de la mémoire partagée
  shm = (COURSIER*)attach_shmem(id_shm);
  for (i = 0; i < MAX_COURSIER; i++) {
    shm[i].pid_coursier = coursiers[i].pid_coursier;
    shm[i].etat = coursiers[i].etat;
  }
  up(id_sem);

  printf(GRN "[HUBERT]" RESET "Connexion à la file de message...\n");
  while (1){
    // Réinitialisation de msg
    msg.type_requete = 0;

    msgrcv(id_file, &msg, sizeof(MSGBUF) - sizeof(long), 1, 0);
    if (msg.type_requete == CHOIX_RESTO) {
      printf(GRN "[HUBERT]" RESET "Le client (%d) désire manger dans un restaurant de type %d !\n", msg.pid_user, msg.type_resto);

      // L'utilisateur a fait un choix dans le type du resto qu'il souhaite
      // On lui renvoie le pid du resto correspondant
      msg.mtype = msg.pid_user;
      msg.pid_user = 0;
      msg.pid_resto = -1;
      for (i = 0; i < NB_RESTO; i++) {
        if (restos[i].type == msg.type_resto) {
          msg.pid_resto = restos[i].pid;
          msg.nb_plat = restos[i].nb_plat;
          i = NB_RESTO;
        }
      }

      if (msg.pid_resto == -1) {
        printf(GRN "[HUBERT]" RESET "Aucun resto correspondant au choix du client n'est connecté au système !\n");
        printf(GRN "[HUBERT]" RESET "N'oubliez pas de démarrer les restos avec \"./resto <type>\" !\n");
        kill(msg.mtype, SIGUSR2);
      }
      msg.type_requete = ID_RESTO;
      msgsnd(id_file, &msg, sizeof(MSGBUF) - sizeof(long), 0);
    } else if (msg.type_requete == ID_RESTO) {
      printf(GRN "[HUBERT]" RESET "Message d'identification du restaurant %d de type %d !\n", msg.pid_resto, msg.type_resto);

      // Au début du programme, les restos envoient leurs identifiants à Hubert
      for (i = 0; i < NB_RESTO; i++) {
        if (restos[i].type == 0) {
          restos[i].type = msg.type_resto;
          restos[i].pid = msg.pid_resto;
          restos[i].nb_plat = msg.nb_plat;
          i = NB_RESTO;
        }
      }

      // Affichage de l'état des restaurants connectés
      printf(GRN "[HUBERT]" RESET "Liste des restaurants en ligne :\n");
      for (i = 0; i < NB_RESTO; i++) {
        if (restos[i].type != 0) {
          printf(GRN "\t[HUBERT]" RESET "Resto %d de type %d\n", restos[i].pid, restos[i].type);
        }
      }
    } else if (msg.type_requete == COMMANDE) {
      printf(GRN "[HUBERT]" RESET "Message de commande en provenance du client %d vers le resto %d !\n", msg.pid_user, msg.pid_resto);

      // Vérifie si un coursier est disponible
      down(id_sem);
      msg.pid_coursier = -1;
      for (i = 0; i < MAX_COURSIER; i++) {
        if (shm[i].etat == 0) {
          msg.pid_coursier = shm[i].pid_coursier;
          shm[i].pid_user = msg.pid_user;
          shm[i].etat = 1;
          i = MAX_COURSIER;
        }
      }
      up(id_sem);

      if (msg.pid_coursier == -1) {
        printf(GRN "[HUBERT]" RESET "Coursier non trouvé\n");
        // Envoie d'un signal d'erreur à l'utilisateur ...
        kill(msg.pid_user, SIGUSR2);
        msg.pid_coursier = 0;
        msg.pid_user = 0;
        msg.id_plat = 0;
      } else {
        printf(GRN "[HUBERT]" RESET "Coursier trouvé !\n");
        // On envoie ensuite la commande au resto
        msg.mtype = msg.pid_resto;
        msg.type_requete = COMMANDE;
        printf(GRN "[HUBERT]" RESET "Envoie commande à resto(%ld), en passant par coursier(%d)\n", msg.mtype, msg.pid_coursier);
        msgsnd(id_file, &msg, sizeof(MSGBUF) - sizeof(long), 0);
      }
    }
  }
}

void coursier() {
  signal(SIGINT, fin_coursier);
  sleep(1);

  // Ouverture de la sémaphore
  id_sem = open_semaphore(getppid());

  // Attachement à la mémoire partagée
  id_shm = open_shmem(getppid(), MAX_COURSIER * sizeof(COURSIER));
  shm = (COURSIER*)attach_shmem(id_shm);
  if (shm == (COURSIER*)(-1)) {
    perror(RED "Erreur d'attachement !\n");
    kill(getppid(), SIGINT);
    exit(1);
  }

  printf(BLU "[COURSIER(%d)]" RESET "Bonjour ! Je suis le coursier %d ! Mon père est %d\n", getpid(), getpid(), getppid());

  while (1) {
    signal(SIGUSR1, plat_ok);
    signal(SIGUSR2, plat_annule);
    pause();
  }
}

void plat_ok() {
  int index = -1, pid_user = 0, i;
  printf(BLU "[COURSIER(%d)]" RESET "Plat ok !\n", getpid());
  down(id_sem);
  for (i = 0; i < MAX_COURSIER; i++) {
    if (shm[i].pid_coursier == getpid()) {
      index = i;
      pid_user = shm[i].pid_user;
      i = MAX_COURSIER;
    }
  }
  up(id_sem);

  if (pid_user != 0) {
    printf(BLU "[COURSIER(%d)]" RESET "Le plat du client %d est prêt !\n", getpid(), pid_user);

    // On génère un nombre aléatoire pour le temps d'attente de transport,
    // puis on prévient l'utilisateur que son plat est livré
    int delai = rand()%(DELAI_MAX - DELAI_MIN) + DELAI_MIN;
    printf(BLU "[COURSIER(%d)]" RESET "Le trajet vers le client %d prendra approx. %d sec ...\n", getpid(), pid_user, delai);
    sleep(delai);
    printf(BLU "[COURSIER(%d)]" RESET "Je suis à la porte du client %d. Le plat vient d'être livré !\n", getpid(), pid_user);
    kill(pid_user, SIGUSR1);

    down(id_sem);
    shm[index].etat = 0;
    shm[index].pid_user = 0;
    up(id_sem);
  }
}

void plat_annule() {
  printf(BLU "[COURSIER(%d)]" RESET "Le plat est annulé !\n", getpid());
  int i;

  down(id_sem);
  for (i = 0; i < MAX_COURSIER; i++) {
    if (shm[i].pid_coursier == getpid()) {
      shm[i].etat = 0;
      if (shm[i].pid_user != 0) {
        kill(shm[i].pid_user, SIGUSR2);
      }
      i = MAX_COURSIER;
    }
  }
  up(id_sem);
}

void fin_coursier() {
  printf(BLU "[COURSIER(%d)]" RESET "J'ai fini de travailler !\n", getpid());
  down(id_sem);
  detach_shmem(shm);
  up(id_sem);
  exit(0);
}

void fin() {
  int i;
  printf(GRN "[HUBERT]" RESET "Arrêt du système...\n");

  // Fin des coursiers
  printf(GRN "[HUBERT]" RESET "Déconnexion des coursiers...\n");
  for (i = 0; i < MAX_COURSIER; i++) {
    kill(coursiers[i].pid_coursier, SIGINT);
    waitpid(coursiers[i].pid_coursier, NULL, 0);
  }

  // Fin des restos
  printf(GRN "[HUBERT]" RESET "Déconnexion des restaurants...\n");
  for (i = 0; i < NB_RESTO; i++) {
    if (restos[i].type != 0) {
      kill(restos[i].pid, SIGINT);
      waitpid(restos[i].pid, NULL, 0);
    }
  }

  printf(GRN "[HUBERT]" RESET "Fermeture des canaux de transmission...\n");
  msgctl(id_file, IPC_RMID, NULL);
  down(id_sem);
  detach_shmem(shm);
  remove_shmem(id_shm);
  up(id_sem);
  remove_semaphore(id_sem);

  printf(GRN "[HUBERT]" RESET "A bientôt !\n");
  exit(0);
}
