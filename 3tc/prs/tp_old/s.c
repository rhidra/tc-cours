/*
Simple udp server
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

void die(char *s) {
  perror(s);
  exit(1);
}

int accepter_connexion(int sock, struct sockaddr_in* client, int slen) {
  printf("Attente d'acceptation ...\n");
  int recv_len;
  struct sockaddr_in addr_client;
  char buf[BUFLEN];
  memset(buf, '\0', BUFLEN);
  if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)client, &slen)) == -1) {
    die("recvfrom()");
  }
  printf("Réception de %s\n", buf);

  if (!strcmp(buf, "SYN")) {
    printf("Demande de connexion d'un client ...\n");

    addr_client = *client;

    strcpy(buf, "SYN-ACK");
    printf("Envoi de l'acquittement (%s)...\n", buf);
    if (sendto(sock, buf, BUFLEN, 0, (struct sockaddr*)client, slen) == -1) {
      die("sendto()");
    }
    printf("Acquittement envoyé (%s) !\n", buf);
    memset(buf, '\0', BUFLEN);
    if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)client, &slen)) == -1) {
      die("recvfrom()");
    }
    printf("Réception de l'acquittement de la synchronisation !\n");

    if (addr_client.sin_addr.s_addr == client->sin_addr.s_addr && strcmp(buf, "ACK")) {
      printf("Le client %s est connecté !\n", inet_ntoa(client->sin_addr));
      printf("Triple handshake over !\n");
      return 0;
    } else {
      die("Echec de connection !");
      return -1;
    }
  }
}

int main(void) {
  struct sockaddr_in si_me, si_other;

  int s, i, slen = sizeof(si_other), recv_len;
  char buf[BUFLEN];

  //create a UDP socket
  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    die("socket");
  }

  // zero out the structure
  memset((char *) &si_me, 0, sizeof(si_me));

  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(PORT);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);

  //bind socket to port
  if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
    die("bind");
  }

  //keep listening for data
  while(1) {
    printf("Waiting for data...\n");
    fflush(stdout);

    accepter_connexion(s, &si_other, slen);

    //try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
      die("recvfrom()");
    }

    //print details of the client/peer and the data received
    printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
    printf("Data: %s\n" , buf);

    //now reply the client with the same data
    if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1) {
      die("sendto()");
    }
  }

  close(s);
  return 0;
}
