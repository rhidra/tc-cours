/*
Simple udp client
*/
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include "pointh.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int connexion(int sock, struct sockaddr_in *addr, int slen) {
    char syn[] = "SYN";
    char ack[] = "ACK-ACK";
    char *type, *chport;
    int len, port;

    //Envoi de la demande connexion
    if (sendto(sock, syn, strlen(syn) , 0 , (struct sockaddr*)addr, slen) == -1) {
        die("Echec de l'envoi du SYN\n");
    }
    printf("SYN envoyé, attente de l'ACK ...\n");

    //Réception du SYN-ACK
    char buf[BUFLEN];
    memset(buf, '\0', BUFLEN);
    if ((len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)addr, &slen)) == -1) {
        die("Echec de la réception de l'ACK-ACK\n");
    }
    printf("Réception de %s\n", buf);

    type = strtok(buf, " ");
    chport = strtok(NULL, " ");
    port = atoi(chport);

    //Traitement du message
    if (!strcmp(type, "SYN-ACK")) {
        //Envoi du ACK-ACK
        if (sendto(sock, ack, strlen(ack) , 0 , (struct sockaddr*)addr, slen) == -1) {
            die("Echec de l'envoi du ACK retour\n");
        }
        addr->sin_port = htons(port);
        printf("Connexion sur le port %d !\n", port);
        printf("ACK-ACK envoyé\n");
        return 0;
    } else {
        die("Attention, le message reçu n'est pas un ACK !\n");
        return -1;
    }
}

int main(void) {
    struct sockaddr_in si_other;
    PACKET pack;
    int s, i, slen=sizeof(si_other), valid=1, recv_len, pack_len = sizeof(pack);
    char buf[BUFLEN];
    char message[BUFLEN];
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000000;
    FILE* file = NULL;
    unsigned int pfile = 0;
    char fichier[80000];
    int fini = 0;

    // Création de la socket
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    // Règlage des paramètres de la socket (timeout, ...)
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &valid, sizeof(int));
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Réglage du port de la socket
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    // Réglage de l'adresse IP de la socket
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    // Tentative de connexion au serveur ...
    connexion(s, &si_other, slen);

    // Ouverture du fichier destination
    if ((file = fopen("TP3_bis.pdf", "wb")) == NULL) {
        die("Ouverture du fichier");
    }

    // Réception du fichier ...
    // int j = 1;
    while(!fini) {
        memset(pack.data, 0, BUFLEN);
        if ((recv_len = recvfrom(s, &pack, pack_len, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
            die("recvfrom()");
        }

        if (!strcmp(pack.data, "STOP")) {
            // Fin de la transmission
            printf("Fin !\n");
            fini = 1;
        } else {
            // Envoi de l'ACK
            sprintf(buf, "ACK_%.*d", SIZE_ACK - 4, pack.seq);
            if (sendto(s, &buf, SIZE_ACK, 0, (struct sockaddr*) &si_other, slen) == -1) {
                die("sendto()");
            }

            // Ecriture dans le buffer
            for (i = 0; i < pack.size/sizeof(char); i++) {
                fichier[pack.seq+i] = pack.data[i];
            }
            pfile += pack.size/sizeof(char);
            // printf("%d - Réception de %d octets (pfile=%d) !\n", j, pack.size, pack.seq);
            // j++;
        }
    }

    // Ecriture dans le fichier
    fwrite(fichier, sizeof(char)*pfile, 1, file);

    // Fermeture du fichier et de la socket
    fclose(file);
    close(s);
    return 0;
}
