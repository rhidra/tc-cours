#ifndef _POINTH_
#define _POINTH_

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //port de la socket de connexion
#define SERVER "127.0.0.1"
#define SIZE_ACK 10 // ACK de la forme "ACK_AAAAAA"
#define RTT_INIT 21
#define RTT_ALPHA 0.5

typedef struct packet {
    int seq;
    int size;
    char data[BUFLEN];
} PACKET;

#endif
