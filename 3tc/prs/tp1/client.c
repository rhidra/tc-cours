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
  if (inet_aton("127.0.0.1", &my_addr.sin_addr) < 0) {
    perror("Erreur : Définition de l'adresse destination !");
    exit(1);
  }

  printf("%d\n", my_addr.sin_addr.s_addr);

  if (connect(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
    perror("Erreur : Connexion au serveur !");
    exit(1);
  }

  char *s = "hello";
  if (write(sock, s, 5*sizeof(char)) < 0) {
    perror("Erreur : Ecriture du message !");
    exit(1);
  }

  sleep(5);

  char *s2 = "hey";
  if (write(sock, s2, 5*sizeof(char)) < 0) {
    perror("Erreur : Ecriture du message !");
    exit(1);
  }

  char msg[10];
  if (read(sock, msg, 10*sizeof(char)) < 0) {
    perror("Erreur : Lecture du message !");
    exit(1);
  }

  printf("%s\n", msg);

  return 0;
}
