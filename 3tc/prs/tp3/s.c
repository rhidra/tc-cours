/*
Simple udp server
*/
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include "pointh.h"

void die(char *s) {
    perror(s);
    exit(1);
}

int creer_socket_data(int port) {
    struct sockaddr_in si_me;
    char buf[BUFLEN];
    int s, i, slen = sizeof(si_me);

    // Création de la socket data
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket bis");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
        die("bind bis");
    }
    printf("Socket Data créée !\n");

    return s;
}

int accepter_connexion(int sock, struct sockaddr_in* client, int slen) {
    printf("Possible d'accepter une connexion ...\n");
    int recv_len, socket_bis, port = 7777;
    struct sockaddr_in addr_client;
    char buf[BUFLEN];
    memset(buf, '\0', BUFLEN);

    // Réception du premier message client
    if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)client, &slen)) == -1) {
        die("Echec de la réception du SYN\n");
    }
    printf("Réception de %s\n", buf);

    // Traitement du message
    if (!strcmp(buf, "SYN")) { //Le message est SYN on traite la connexion
        printf("Demande de connexion d'un client ...\n");
        addr_client = *client;

        socket_bis = creer_socket_data(port);

        // Envoi de la réponse du SYN-ACK
        sprintf(buf, "SYN-ACK %d", port);
        printf("Envoi de l'acquittement (%s)...\n", buf);
        if (sendto(sock, buf, BUFLEN, 0, (struct sockaddr*)client, slen) == -1) {
            die("Echec de l'envoi de du SYN-ACK");
        }
        printf("Acquittement envoyé (%s), attente de l'ACK-ACK ...\n", buf);
        memset(buf, '\0', BUFLEN);

        // RéZception du ACK-ACK
        if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)client, &slen)) == -1) {
            die("Echec de la réception d'ACK-ACK\n");
        }
        printf("Message reçu pour ACK-ACK: %s\n", buf);
        if(!strcmp(buf, "ACK-ACK")) {
            printf("Réception de l'acquittement final !\n");
        } else {
            printf("Echec de la connexion: pas de ACK final\n");
        }

        if (addr_client.sin_addr.s_addr == client->sin_addr.s_addr && strcmp(buf, "ACK")) {
            printf("Le client %s est connecté !\n", inet_ntoa(client->sin_addr));
            printf("Triple handshake over !\n");
            return socket_bis;
            // Le message n'est pas un SYN, echec ...
        } else {
            die("Echec de connexion !");
            return -1;
        }
    }
}

int estimation_rtt(int time_send, int time_recv, int srtt) {
    printf("%d\n", (time_recv-time_send));
    int rtt = RTT_ALPHA * srtt + (1 - RTT_ALPHA) * (time_recv - time_send);
    printf("RTT = %d\n", rtt);
    return rtt;
}

int main(void) {
    struct sockaddr_in si_me, si_other;
    PACKET pack;
    char buf[BUFLEN], ack[BUFLEN];
    int s, sock_data, i, slen = sizeof(si_other), recv_len, file_size;
    int pack_len = sizeof(pack), seq = 0;
    FILE* file = NULL;
    int rtt = RTT_INIT, time_send = 0, time_recv = 0;
    int cwnd = 1, flightSize = 0;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = rtt;

    // Création de la socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    // Réglage de l'adresse IP et du port
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind de la socket au port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
        die("bind");
    }

    // Attente de connexion ...
    sock_data = accepter_connexion(s, &si_other, slen);

    // Ouverture du fichier source
    if ((file = fopen("TP3.pdf", "rb")) == NULL) {
        die("Ouverture du fichier");
    }

    // fseek(file, 0, SEEK_END); // seek to end of file
    // file_size = ftell(file); // get current file pointer
    // fseek(file, 0, SEEK_SET); // seek back to beginning of file
    // printf("Ouverture du fichier de taille %d octets\n", file_size);

    // Envoi du fichier ...
    // int j = 1;
    while((pack.size = fread(pack.data, sizeof(char), BUFLEN, file)) != 0) {
        // printf("%d - Transmission de %d octets...\n", j, pack.size);
        // j++;
        pack.seq = seq;
        time_send = clock();
        if (sendto(sock_data, &pack, pack_len, 0, (struct sockaddr*) &si_other, slen) == -1) {
            die("sendto()");
        }
        seq += pack.size;

        flightSize++;

        // Si la fenêtre de congestion est remplie ...
        if (flightSize == cwnd) {
            // Réglage du timeout sur le RTT
            tv.tv_usec = rtt;
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

            // Attente de l'ACK
            if ((recv_len = recvfrom(sock_data, &ack, SIZE_ACK, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                // Timeout !
                die("recvfrom()");
            } else {
                // ACK reçu !
                printf("ACK reçu : %s; cwnd=%d\n", ack, cwnd);
                memset(buf, '\0', BUFLEN);
                memset(ack, '\0', BUFLEN);

                // Incrémentation de la fenêtre
                cwnd++;
                flightSize--;

                // Estimation du RTT
                time_recv = clock();
                rtt = estimation_rtt(time_send, time_recv, rtt);
            }
        }
    }

    // Fermeture du fichier
    printf("Transmission de %d octets terminé !\n", ftell(file));
    fclose(file);

    // Fin de la transmission
    memset(pack.data, '\0', BUFLEN);
    printf("Transmission de STOP ...\n");
    strcpy(pack.data, "STOP");
    pack.size = 4;
    if (sendto(sock_data, &pack, pack_len, 0, (struct sockaddr*) &si_other, slen) == -1) {
        die("sendto()");
    }

    // Fermeture de la socket
    close(s);
    return 0;
}
