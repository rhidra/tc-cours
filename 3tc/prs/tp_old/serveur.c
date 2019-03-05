#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define RCVSIZE 1024

int main (int argc, char *argv[]) {

  struct sockaddr_in adresse, client;
  int port= 5001;
  int valid= 1;
  char buffer[RCVSIZE];

  //create socket
  int desc= socket(AF_INET, SOCK_DGRAM, 0);

  // handle error
  if (desc < 0) {
    perror("cannot create socket\n");
    return -1;
  }

  setsockopt(desc, SOL_SOCKET, SO_REUSEADDR, &valid, sizeof(int));

  adresse.sin_family= AF_INET;
  adresse.sin_port= htons(port);
  adresse.sin_addr.s_addr= htonl(INADDR_ANY);

  if (bind(desc, (struct sockaddr*) &adresse, sizeof(adresse)) == -1) {
    perror("Bind fail\n");
    close(desc);
    return -1;
  }

  while (1) {
    // int msgSize = recv(desc,buffer,RCVSIZE,0);
    int msgSize = recvfrom(desc, buffer, RCVSIZE, 0, (struct sockaddr*)&client, sizeof(client));
    printf("Message reçu !\n");

    // while (msgSize > 0) {
    sendto(desc,buffer,msgSize,0, (struct sockaddr*)&client, sizeof(client));
    printf("%s",buffer);
    memset(buffer,0,RCVSIZE);
    printf("Fin de traitement du message !\n");
    // msgSize= recv(desc,buffer,RCVSIZE,0);
    // }

    // close(desc);

  }

  close(desc);
  return 0;
}
