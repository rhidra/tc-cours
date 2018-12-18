#include "resto.h"
#include <time.h>

int id_sem;
PLAT* addr_shmem;
int pid_coursier;
int descpipe[2];
int pid_cuisine;
int id_shmem;

int main(int argc, char* argv[]) {
	printf(CYN "[RESTO(%d)]" RESET "Connexion du restaurant ...\n", getpid());
	if(argc < 2) {
		perror(RED "Il faut donner le type du resto.\n");
		exit(1);
	}

	int pid_resto = getpid();
	int type_resto = atoi(argv[1]);

	int key_sem = pid_resto;
	int id_sem;

	int key_shmem = pid_resto;
	int taille_shmem;
	int nb_plat;

	//Initialisation taille_shmem
	switch(type_resto) {
		case CHINOIS:
		taille_shmem = NOMBRE_PLAT_CHINOIS * sizeof(PLAT);
		nb_plat = NOMBRE_PLAT_CHINOIS;
		break;
		case ITALIEN:
		taille_shmem = NOMBRE_PLAT_ITALIEN * sizeof(PLAT);
		nb_plat = NOMBRE_PLAT_ITALIEN;
		break;
		case FASTFOOD:
		taille_shmem = NOMBRE_PLAT_FASTFOOD * sizeof(PLAT);
		nb_plat = NOMBRE_PLAT_FASTFOOD;
		break;
	}

	//Création tube anonyme
	if(pipe(descpipe) == -1) {
		perror(RED "Erreur lors de la création du tube anonyme.\n");
		exit(1);
	}

	pid_cuisine = fork();

	if(pid_cuisine == -1) {
		perror(RED "Echec de la création du processus cuisine.\n");
		exit(1);
		//------------------------------------processus père - resto ------------------------------------
	} else if(pid_cuisine > 0) {
		int key_file;
		int id_file;
		int quantite_plat;
		int id_plat;
		MSGBUF msg_recu;

		//Connexion à la file de messages
		key_file = ftok("hubert.c", 0);
		id_file = msgget(key_file, S_IRUSR |S_IWUSR);
		if(id_file == -1) {
			perror(RED "Erreur : file de message non créée ! Merci de démarrer le serveur Hubert !\n");
			fin_resto();
		}

		//Envoie message à Hubert pour donner son pid
		MSGBUF msg_rid = creer_message(1, ID_RESTO, 0, pid_resto, 0, type_resto, 0, nb_plat);
		if (msgsnd(id_file, &msg_rid, sizeof(MSGBUF) - sizeof(long), 0) == -1) {
			perror(RED "Erreur : file de message non créée ! Merci de démarrer le serveur Hubert !\n");
			fin_resto();
		}

		//Création mutex
		id_sem = create_semaphore(key_sem);
		if(id_sem == -1) {
			perror(RED "Erreur lors de la création de sem par resto.\n");
			fin_resto();
		}

		//Init mutex
		init_semaphore(id_sem, 0);

		//Création shmem
		id_shmem = create_shmem(key_shmem, taille_shmem);
		if(id_shmem == -1) {
			perror(RED "Erreur lors de la création de shmem_resto par resto.\n");
			exit(1);
		}

		//Attachement shmem
		addr_shmem = (PLAT*)attach_shmem(id_shmem);
		if((addr_shmem) == (PLAT*)-1) {
			perror(RED "Erreur lors de l'attachement à shmem_resto.\n");
			exit(1);
		}

		//Init shmem
		init_shmem(type_resto, addr_shmem, id_sem);
		up(id_sem);

		//Init fonction rand
		srand(time(NULL));

		//Je ne me sers pas du tube en lecture
		close(descpipe[0]);

		printf(CYN "[RESTO(%d)]" RESET "Le restaurant est connecté à Hubert !\n", getpid());
		while(1) {
			msg_recu.type_requete = 0;

			//Redirection du signal fin de programme (^C: SIGINT)
			signal(SIGINT, fin_resto);

			//Redirection du signal commande prete (SIG_USR1)
			signal(SIGUSR1, commande_prete);

			//Redirection du signal commande impossible (SIG_USR2)
			signal(SIGUSR2, commande_impossible);

			msgrcv(id_file, &msg_recu, sizeof(MSGBUF) - sizeof(long), pid_resto, 0);
			if (msg_recu.type_requete != 0) {
				id_plat = msg_recu.id_plat;
				pid_coursier = msg_recu.pid_coursier;

				quantite_plat = 0;

				if (msg_recu.id_plat > nb_plat || msg_recu.id_plat <= 0) {
					printf(CYN "[RESTO(%d)]" RESET "Le plat demandé n'existe pas !\n", getpid());
					commande_impossible();
				} else {
					//accès à la mémoire partagée pour avoir le stock
					down(id_sem);
					quantite_plat = addr_shmem[msg_recu.id_plat - 1].quantite;
					up(id_sem);
					printf(CYN "[RESTO(%d)]" RESET "Commande du plat %d, pour le client %d. Il reste %d plat(s) préparé(s).\n", getpid(), msg_recu.id_plat, msg_recu.pid_user, quantite_plat);

					if(quantite_plat >= 1) {
						down(id_sem);
						addr_shmem[msg_recu.id_plat -1].quantite--;
						up(id_sem);
						commande_prete(); //indique au coursier que la commande est prete
					} else if (quantite_plat == 0) {
						printf(CYN "[RESTO(%d)]" RESET "Il n'y a plus assez de ce plat en réserve !\n", getpid());
						write(descpipe[1], &id_plat, sizeof(int));
						pause();
					} else {
						perror(RED "Erreur : quantité d'un plat inférieure à 0 !\n");
						fin_resto();
					}
				}
			}
		}

		//-------------------------------------processus fils - cuisine ---------------------------------
	} else if(pid_cuisine == 0) {
		int id_plat, delai;
		sleep(1);
		printf(YEL "[CUISINE(%d)]" RESET "Connexion de la cuisine ...\n", getpid());

		//Ouverture mutex
		id_sem = open_semaphore(key_sem);
		if(id_sem == -1) {
			perror(RED "Erreur lors de l'ouverture de la semaphore par cuisine.\n");
			exit(1);
		}

		//Attachement à shmem_resto
		down(id_sem);
		id_shmem = open_shmem(key_shmem, taille_shmem);
		addr_shmem = (PLAT*)attach_shmem(id_shmem);
		if(addr_shmem == (PLAT*)-1) {
			perror(RED "Erreur lors de l'attachement à shmem_resto par cuisine.\n");
			exit(1);
		}
		up(id_sem);

		//Je ne me sers pas du tube en ecriture
		close(descpipe[1]);

		//Redirection du signal fin de programme (^C: SIGINT)
		signal(SIGINT, fin_cuisine);

		printf(YEL "[CUISINE(%d)]" RESET "La cuisine est connectée !\n", getpid());
		while(1) {
			read(descpipe[0], &id_plat, sizeof(int));
			printf(YEL "[CUISINE(%d)]" RESET "Réception d'un message pour la cuisine !\n", getpid());
			if((rand()%10) < 9) {
				// Le plat pourra être préparé à temps
				delai = rand()%(6-2)+2;
				printf(YEL "[CUISINE(%d)]" RESET "Je me depêche de préparer le plat ! Je devrais en avoir pour %d sec !\n", getpid(), delai);
				sleep(delai);
				kill(pid_resto, SIGUSR1);
			} else {
				// Le plat prendre trop de temps à être préparé
				// On annule la commande mais on prépare quand même le plat
				delai = rand()%(15-7)+7;
				printf(YEL "[CUISINE(%d)]" RESET "Malheureusement, le plat ne pourra pas être prêt à temps ! Il sera renouvelé dans %d sec...\n", getpid(), delai);
				kill(pid_resto, SIGUSR2);
				sleep(delai);
				printf(YEL "[CUISINE(%d)]" RESET "Le plat a fini d'être préparé !\n", getpid());
				down(id_sem);
				addr_shmem[id_plat - 1].quantite++;
				up(id_sem);
				printf(YEL "[CUISINE(%d)]" RESET "Le plat est prêt !!\n", getpid());
			}
		}
	}

	return 1;
}

void fin_cuisine() {
	printf(YEL "[CUISINE(%d)]" RESET "Déconnexion de la cuisine !\n", getpid());
	close(descpipe[0]);
	detach_shmem(addr_shmem);
	exit(0);
}

void fin_resto() {
	kill(pid_cuisine, SIGINT);
	close(descpipe[1]);
	waitpid(pid_cuisine, NULL, 0);
	detach_shmem(addr_shmem);
	remove_shmem(id_shmem);
	remove_semaphore(id_sem);
	printf(CYN "[RESTO(%d)]" RESET "Déconnexion du restaurant au système Hubert !\n", getpid());
	exit(0);
}

void commande_prete() {
	printf(CYN "[RESTO(%d)]" RESET "Commande prete (pid_coursier=%d)\n", getpid(), pid_coursier);
	kill(pid_coursier, SIGUSR1);
}

void commande_impossible() {
	kill(pid_coursier, SIGUSR2);
}

void init_shmem(int type_resto, PLAT* addr_shmem, int id_sem) {
	switch(type_resto) {
		case CHINOIS:
		addr_shmem[0].id_plat = 1;
		//printf("id_plat(resto): %d\n", addr_shmem[0].id_plat);
		addr_shmem[0].quantite = 2;
		strcpy(addr_shmem[0].nom_plat, "Nems");
		addr_shmem[1].id_plat = 2;
		//printf("id_plat(resto): %d\n", addr_shmem[1].id_plat);
		addr_shmem[1].quantite = 2;
		strcpy(addr_shmem[1].nom_plat, "Nouilles");
		addr_shmem[2].id_plat = 3;
		//printf("id_plat(resto): %d\n", addr_shmem[2].id_plat);
		addr_shmem[2].quantite = 2;
		strcpy(addr_shmem[2].nom_plat, "Riz");
		break;
		case ITALIEN:
		addr_shmem[0].id_plat = 1;
		//printf("id_plat(resto): %d\n", addr_shmem[0].id_plat);
		addr_shmem[0].quantite = 2;
		strcpy(addr_shmem[0].nom_plat, "Pizza");
		addr_shmem[1].id_plat = 2;
		//printf("id_plat(resto): %d\n", addr_shmem[1].id_plat);
		addr_shmem[1].quantite = 2;
		strcpy(addr_shmem[1].nom_plat, "Penne");
		addr_shmem[2].id_plat = 3;
		//printf("id_plat(resto): %d\n", addr_shmem[2].id_plat);
		addr_shmem[2].quantite = 2;
		strcpy(addr_shmem[2].nom_plat, "Gelato");
		break;
		case FASTFOOD:
		addr_shmem[0].id_plat = 1;
		//printf("id_plat(resto): %d\n", addr_shmem[0].id_plat);
		addr_shmem[0].quantite = 2;
		strcpy(addr_shmem[0].nom_plat, "Hamburger");
		addr_shmem[1].id_plat = 2;
		//printf("id_plat(resto): %d\n", addr_shmem[1].id_plat);
		addr_shmem[1].quantite = 2;
		strcpy(addr_shmem[1].nom_plat, "Frites");
		addr_shmem[2].id_plat = 3;
		//printf("id_plat(resto): %d\n", addr_shmem[2].id_plat);
		addr_shmem[2].quantite = 2;
		strcpy(addr_shmem[2].nom_plat, "Nuggets");
		addr_shmem[3].id_plat = 4;
		//printf("id_plat(resto): %d\n", addr_shmem[3].id_plat);
		addr_shmem[3].quantite = 2;
		strcpy(addr_shmem[3].nom_plat, "Wrap");
		break;
	}
}
