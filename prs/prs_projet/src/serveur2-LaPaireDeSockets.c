#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

// Paquet = 6 octets de header + DATA_SIZE octets de données
#define MAX_PACKET_SIZE 1500
#define HEADER_SIZE 6
#define DATA_SIZE 1494
#define SIZE_ACK 10 // ACK de la forme "ACK_AAAAAA"
#define SLOW_LIMIT 1000 //nombre de paquets limite du slow star
#define SLOW_INC 50 //incrémentation lors du slow start
#define SLOW_DEC 10
#define SLOW_INIT 200 //Initialisation du slow start
#define NB_ENVOIS_INIT 1

void die(char *s) {
    perror(s);
    exit(1);
}

int creer_socket_data(int port) {
    struct sockaddr_in si_me;
    int s, sock_len = sizeof(si_me);

    // Création de la socket data
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("Echec lors de la création de la socket data");
    }

    // Initialisation de la structure à zéro
    memset((char *) &si_me, 0, sock_len);

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    // Liaison de la socket au port
    if( bind(s , (struct sockaddr*)&si_me, sock_len) == -1) {
        die("Echec lors du bind de la socket data");
    }

    return s;
}

int accepter_connexion(int sock, struct sockaddr_in* client, int sock_len) {
    int recv_len, socket_data, port = 7777;
    struct sockaddr_in addr_client;
    char data[DATA_SIZE];
    memset(data, '\0', DATA_SIZE);

    // Réception du premier message client
    if ((recv_len = recvfrom(sock, data, DATA_SIZE, 0, (struct sockaddr*)client, &sock_len)) == -1) {
        die("Echec de la réception du SYN\n");
    }

    // Traitement du message
    if (!strcmp(data, "SYN")) { //Le message est SYN on traite la connexion
        addr_client = *client;

        //Création de la socket de data
        socket_data = creer_socket_data(port);

        // Envoi de la réponse SYN-ACK
        sprintf(data, "SYN-ACK%d", port);
        if (sendto(sock, data, DATA_SIZE, 0, (struct sockaddr*)client, sock_len) == -1) {
            die("Echec de l'envoi de du SYN-ACK");
        }
        memset(data, '\0', DATA_SIZE);

        // Réception du ACK
        if ((recv_len = recvfrom(sock, data, DATA_SIZE, 0, (struct sockaddr*)client, &sock_len)) == -1) {
            die("Echec de la réception d'ACK\n");
        }

        if ((addr_client.sin_addr.s_addr == client->sin_addr.s_addr) && (!strcmp(data, "ACK"))) {
            return socket_data;
            // Le message n'est pas un SYN, echec ...
        } else {
            die("Echec de connexion: pas de ACK final !\n");
            return -1;
        }
    }

    return -1;
}

int parseACK(char* ack) {
	char num[6];
	int i;

	for(i = 0; i < 6; i++) {
		num[i] = ack[4+i];
	}

	return (int)strtol(num,NULL, 10);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./serveur2-LaPaireDeSockets <port>\n");
        exit(1);
    }
    int port = (int)strtol(argv[1], NULL, 10);
    if (port == 0) {
        printf("Merci de rentrer un numéro de port valide !\n");
        exit(1);
    }

    struct sockaddr_in si_me, si_other;
    char data[DATA_SIZE], ack[SIZE_ACK], msg[DATA_SIZE + HEADER_SIZE];
    int s, sock_data, sock_len = sizeof(si_other), recv_len, packet_size, data_size;
    int seq = 1, num_ack;
    FILE* file = NULL;
    int cwnd = SLOW_INIT;
    int old_cwnd = SLOW_INIT;

    int nb_envois = NB_ENVOIS_INIT;
    int nb_envois_futur = NB_ENVOIS_INIT;

    int ack_actuel = 0;

    int fichier_fini = 0; // Booléen de sortie de la boucle d'envoie du fichier

    int i, j; //indices des boucles

    // Création de la socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    // Réglage de l'adresse IP et du port
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind de la socket au port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
        die("bind");
    }

    // Attente de connexion ...
    sock_data = accepter_connexion(s, &si_other, sock_len);
    printf("Début de la transmission\n");

    // Timeout en réception des paquets
    struct timeval tv;
    tv.tv_sec = 0; // Temps en secondes
    tv.tv_usec = 10000; // Temps en microsecondes

    memset(data, '\0', DATA_SIZE);
    if ((recv_len = recvfrom(sock_data, &data, DATA_SIZE, 0, (struct sockaddr *) &si_other, &sock_len)) == -1) {
        // Timeout ! Echec de connexion !
        die("Timeout ! Le nom du fichier n'a pas été reçu !\n");
    }

    // Ouverture du fichier source
    if ((file = fopen(data, "rb")) == NULL) {
        die("Ouverture du fichier");
    }

    //Boucle d'envoi du fichier
    //On boucle tant que le fichier n'est pas fini
    while(!fichier_fini) {
		//Envoi d'une rafale de paquets
		for(j = 0; j < old_cwnd; j++) {
            //Si il y a encore des données
			if((data_size = fread(data, sizeof(char), DATA_SIZE, file)) != 0) {
				//Initialisation du paquet
				memset(msg, '\0', DATA_SIZE + HEADER_SIZE);
				packet_size = data_size + HEADER_SIZE;

				//Ecriture de la seq
				sprintf(msg, "%6d", seq);
				for (i = 0; i < HEADER_SIZE; i++){
                    if (msg[i] == ' ')
                        msg[i] = '0';
				}

				//Ecriture de la data
				for (i = HEADER_SIZE; i < packet_size; i++) {
                    msg[i] = data[i-HEADER_SIZE];
				}
                seq++;

				// Envoi du paquet
                for(i = 0; i < nb_envois; i++) {
				    if (sendto(sock_data, &msg, packet_size, 0, (struct sockaddr*) &si_other, sock_len) == -1)
                        die("Echec de l'envoi d'un paquet\n");
                }

            //sinon on sort de la boucle
			} else {
				fichier_fini = 1;
			}
        }

        //Mise en place du time out
        setsockopt(sock_data, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        //Reception des ACK
        // for(j= 0; j < old_cwnd*nb_envois; j++) {
        int stop = 0;
        while(!stop) {
            // Attente de l'ACK
            if ((recv_len = recvfrom(sock_data, &ack, SIZE_ACK, 0, (struct sockaddr *) &si_other, &sock_len)) == -1) {
                // Timeout ! Un paquet perdu ...
                stop = 1;
                // nb_envois_futur++;
            } else {
                // On a reçu quelque chose
                // if(nb_envois_futur > 1)
                //     nb_envois_futur --;
                num_ack = parseACK(ack);
                memset(ack, '\0', SIZE_ACK);

                if (num_ack > ack_actuel) {
                    ack_actuel = num_ack;
                }
            }
        }

        // On analyse le dernier ACK reçu
        if (ack_actuel != seq-1) {
            // Des paquets n'ont pas été reçus !
            // On retransmet depuis le dernier paquet reçu
            fichier_fini = 0;
            fseek(file, (ack_actuel)*DATA_SIZE, SEEK_SET);
            seq = ack_actuel+1;
            if (cwnd - SLOW_DEC < SLOW_INIT)
                cwnd = SLOW_INIT;
            else
                cwnd -= SLOW_DEC;
        } else {
            cwnd += SLOW_INC;
        }

        old_cwnd = cwnd;
        memset(data, '\0', DATA_SIZE);
        memset(ack, '\0', SIZE_ACK);
    }

    // Fermeture du fichier
    fclose(file);

    // Fin de la transmission - envoi du mot FIN
    memset(data, '\0', DATA_SIZE);
    strcpy(data, "FIN");
    for (i = 0; i < 100000; i++) {
        if (sendto(sock_data, &data, DATA_SIZE, 0, (struct sockaddr*) &si_other, sock_len) == -1) {
            die("Echec de la transmission de FIN");
        }
    }
    printf("Fin de la transmission\n");

    // Fermeture de la socket
    close(s);
    return 0;
}
