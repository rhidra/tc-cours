#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
  int reuse = 1;
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Erreur : Création de la socket !");
    exit(1);
  }
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  printf("socket = %d\n", sock);

  struct sockaddr_in my_addr;
  memset((char*) &my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(4343);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  printf("%d\n", (my_addr.sin_addr.s_addr));

  bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr));

  listen(sock, 1);

  struct sockaddr_in client;
  memset((char*) &client, 0, sizeof(client));
  unsigned int len = (unsigned int)sizeof(client);

  int sock_data;
  while(1) {
    if ((sock_data = accept(sock, (struct sockaddr*)&client, &len)) < 0) {
      perror("Erreur : Acceptation de la connexion !");
      exit(1);
    }

    char msg[10];
    char msg2[10];
    if (read(sock_data, msg, 10*sizeof(char)) < 0) {
      perror("Erreur : Lecture du message !");
      exit(1);
    }
    if (read(sock_data, msg2, 10*sizeof(char)) < 0) {
      perror("Erreur : Lecture du message !");
      exit(1);
    }

    if (write(sock_data, msg, 10*sizeof(char)) < 0) {
      perror("Erreur : Ecriture du message !");
      exit(1);
    }

    printf("msg=%s\n", msg);
    printf("msg2=%s\n", msg2);
    printf("ip=%d\n", ntohl(client.sin_addr.s_addr));
    printf("port=%d\n", ntohs(client.sin_port));
  }
  return 0;
}
