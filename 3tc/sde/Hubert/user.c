#include "user.h"

PLAT* addr_shmem;
int id_sem;

int main() {
	int key_file;
	int id_file;
	int id_resto;
	int id_plat;
	int fini = 0;
	MSGBUF msg_recu;
	MSGBUF msg_choix_resto;
	MSGBUF msg_choix_plat;
	int key_shmem;
	int id_shmem;
	int taille_shmem;
	int key_sem;
	int id_sem;
	int i;

	//Connection à la file de messages
	key_file = ftok("hubert.c", 0);
	id_file = msgget(key_file, S_IRUSR |S_IWUSR);
	if(id_file == -1) {
		perror(RED "Erreur : file de message non créée ! Merci de démarrer le serveur Hubert !\n");
		exit(1);
	}

	//Redirection du signal fin de programme (^C: SIGINT)
	signal(SIGINT, fin_user);

	//Redirection du signal commande prete (SIG_USR1)
	signal(SIGUSR1, commande_prete);

	//Redirection du signal commande impossible (SIG_USR2)
	signal(SIGUSR2, commande_impossible);

	while(fini == 0) {
		printf(MAG "[USER(%d)]" RESET "Tapez le numéro correspondant au restaurant dont vous voulez voir le menu puis appuyez sur entrée.\n", getpid());
		printf("\t1. Chinois\n\t2. Italien\n\t3. Fast Food\n");
		printf(MAG "[USER(%d)]" RESET "Restaurant : ", getpid());
		scanf("%d", &id_resto);
		if (id_resto > 3 || id_resto <= 0) {
			perror(RED "Erreur : Merci de rentrer un caractère convenable !\n");
			exit(1);
		}

		printf(MAG "[USER(%d)]" RESET "Récupération du menu par le serveur Hubert ...\n", getpid());
		//Envoie message à Hubert avec le nom du resto dont on veut voir le menu
		msg_choix_resto = creer_message(1, CHOIX_RESTO, getpid(), 0, 0, id_resto, 0, 0);
		msgsnd(id_file, &msg_choix_resto, sizeof(MSGBUF) - sizeof(long), 0);
		msgrcv(id_file, &msg_recu, sizeof(MSGBUF) - sizeof(long), getpid(), 0);

		if(msg_recu.type_requete == ID_RESTO) {
			taille_shmem = msg_recu.nb_plat * sizeof(PLAT);

			//Ouverture mutex
			key_sem = msg_recu.pid_resto;
			id_sem = open_semaphore(key_sem);
			if(id_sem == -1) {
				perror(RED "Erreur lors de l'ouverture de sem par user.\n");
				exit(1);
			}

			//Attachement shmem
			down(id_sem);
			key_shmem = msg_recu.pid_resto;
			id_shmem = open_shmem(key_shmem, taille_shmem);
			addr_shmem = (PLAT*)attach_shmem(id_shmem);
			if((addr_shmem) == (PLAT*)-1) {
				perror(RED "Erreur lors de l'attachement à shmem_resto.\n");
				exit(1);
			}

			int j = 0;
			//Lecture et affichage de shmem
			printf(MAG "[USER(%d)]" RESET "Voici le menu du restaurant choisi.\n", getpid());
			for(i= 0; i < taille_shmem/sizeof(PLAT); i++) {
				printf("\t%d. ", addr_shmem[i].id_plat);
				j = 0;
				while (addr_shmem[i].nom_plat[j] != '\0') {
					printf("%c", addr_shmem[i].nom_plat[j]);
					j++;
				}
				printf("\n");
			}
			up(id_sem);

			printf(MAG "[USER(%d)]" RESET "Tapez le numéro correspondant au plat souhaité puis appuyez sur entrée. Si vous voulez voir un autre menu, tapez 0.\n", getpid());
			printf(MAG "[USER(%d)]" RESET "Commande : ", getpid());
			scanf("%d", &id_plat);
			if (id_plat <= 10 && id_plat > 0) {
				fini = 1;
			} else if(id_plat != 0) {
				fini = 1;
				perror(RED "Erreur : Merci de rentrer un caractère convenable !\n");
				exit(1);
			}
		}
	}

	msg_choix_plat = creer_message(1, COMMANDE, getpid(), msg_recu.pid_resto, 0, id_resto, id_plat, 0);
	msgsnd(id_file, &msg_choix_plat, sizeof(MSGBUF) - sizeof(long), 0);

	pause();

	return 1;
}

void fin_user() {
	down(id_sem);
	detach_shmem(addr_shmem);
	up(id_sem);
	exit(0);
}

void commande_prete() {
	printf(MAG "[USER(%d)]" RESET "Votre commande vient d'être livrée, bon appétit !\n", getpid());
	exit(0);
}

void commande_impossible() {
	printf(MAG "[USER(%d)]" RESET "Nous sommes désolés, votre commande ne peut pas être livrée...\n", getpid());
	exit(0);
}
