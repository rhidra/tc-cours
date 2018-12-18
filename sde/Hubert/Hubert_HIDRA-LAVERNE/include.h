#ifndef _INCLUDE_H_
#define _INCLUDE_H_

// Type de requête
#define CHOIX_RESTO 1
#define ID_RESTO 2
#define COMMANDE 3

// Couleur dans le terminal
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

// Structure d'un message
typedef struct msgbuf {
  // 1 si le message est pour le Hubert
  // sinon, pid du processus destination
  long mtype;

  int type_requete;
  int pid_user;
  int pid_resto;
  int pid_coursier;
  int type_resto;
  int id_plat;
  int nb_plat;
} MSGBUF;

// Création d'un message
MSGBUF creer_message(long mtype, int rtype, int pid_user, int pid_resto, int pid_coursier, int type_resto, int id_plat, int nb_plat) {
	MSGBUF temp;

	temp.mtype = mtype;
	temp.type_requete = rtype;
	temp.pid_user = pid_user;
	temp.pid_resto = pid_resto;
	temp.pid_coursier = pid_coursier;
	temp.type_resto = type_resto;
	temp.id_plat = id_plat;
  temp.nb_plat = nb_plat;

	return temp;
}

#endif
