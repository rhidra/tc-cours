#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>

#define RCVSIZE 1024

int main (int argc, char *argv[]) {

  if (argc != 3) {
    printf("Merci de rentrer un nombre correct de paramètres !\n");
    printf("./serveur <port_serveur1> <port_serveur2>");
    exit(1);
  }

  struct sockaddr_in adresse1, adresse2, client;
  int port1= atoi(argv[1]);
  int port2= atoi(argv[2]);
  int valid= 1;
  socklen_t alen= sizeof(client);
  char buffer[RCVSIZE];
  int pid;

  //create socket
  int desc1= socket(AF_INET, SOCK_STREAM, 0);
  int desc2= socket(AF_INET, SOCK_DGRAM, 0);
  printf("Socket serveur 1 = %d\n", desc1);
  printf("Socket serveur 2 = %d\n", desc2);

  // handle error
  if (desc1 < 0 || desc2 < 0) {
    perror("cannot create socket\n");
    return -1;
  }

  setsockopt(desc1, SOL_SOCKET, SO_REUSEADDR, &valid, sizeof(int));
  setsockopt(desc2, SOL_SOCKET, SO_REUSEADDR, &valid, sizeof(int));

  adresse1.sin_family= AF_INET;
  adresse1.sin_port= htons(port1);
  adresse1.sin_addr.s_addr= htonl(INADDR_ANY);

  adresse2.sin_family= AF_INET;
  adresse2.sin_port= htons(port2);
  adresse2.sin_addr.s_addr= htonl(INADDR_ANY);

  if (bind(desc1, (struct sockaddr*) &adresse1, sizeof(adresse1)) == -1
  || bind(desc2, (struct sockaddr*) &adresse2, sizeof(adresse2)) == -1) {
    perror("Bind fail\n");
    close(desc1);
    close(desc2);
    return -1;
  }

  if (listen(desc1, 5) < 0) {
    perror("Listen 1 failed\n");
    return -1;
  }

  fd_set *set = (fd_set*)malloc(sizeof(fd_set));

  while (1) {
    int rqst, result = -1;
    do {
      FD_ZERO(set);
      FD_SET(desc1, set);
      FD_SET(desc2, set);
      printf("Avant select\n");
      result = select(desc2 + 1, NULL, set, NULL, NULL);
      printf("Après select %d\n", result);
    } while (result == -1);

    if (FD_ISSET(desc1, set)) {
      printf("Connexion 1 ...\n");
      rqst= accept(desc1, (struct sockaddr*)&client, &alen);

      if ((pid = fork()) == 0) { // Processus fils
        printf("Socket client = %d\n", rqst);
        int msgSize= recv(rqst,buffer,RCVSIZE,0);

        while (msgSize > 0) {
          send(rqst,buffer,msgSize,0);
          printf("%s",buffer);
          memset(buffer,0,RCVSIZE);
          msgSize= recv(rqst,buffer,RCVSIZE,0);
        }

        close(rqst);
        exit(0);
      } else if (pid > 0) {
        // Processus père
        //printf("Pid du fils : %d\n", pid);
        close(rqst);
      } else {
        perror("Erreur : Fork\n");
        exit(1);
      }
    } else if (FD_ISSET(desc2, set)) {
      printf("Connexion 2 ...\n");
      recv(desc2, buffer, RCVSIZE, 0);
      printf("%s", buffer);
      memset(buffer, 0, RCVSIZE);
    } else {
      perror("Erreur : select\n");
      exit(1);
    }

  }

  free(set);
  close(desc1);
  close(desc2);
  return 0;
}
