/*
Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data

void die(char *s)
{
  perror(s);
  exit(1);
}

int connexion(int sock, struct sockaddr_in *addr, int slen) {
  char syn[] = "SYN";
  int len;
  if (sendto(sock, syn, strlen(syn) , 0 , (struct sockaddr*)addr, slen) == -1) {
    die("sendto()");
  }

  char buf[BUFLEN];
  memset(buf, '\0', BUFLEN);
  printf("buf:%s\n", buf);
  if ((len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)addr, &slen)) == -1) {
    die("recvfrom connexion");
  }
  printf("Réception de %s (%d)\n", buf, len);

  if (!strcmp(buf, "SYN-ACK")) {
    printf("Connection établie !\n");
    return 0;
  } else {
    die("/!\\ Erreur de connection ! /!\\");
    return -1;
  }
}

int main(void) {
  struct sockaddr_in si_other;
  int s, i, slen=sizeof(si_other), valid=1;
  char buf[BUFLEN];
  char message[BUFLEN];
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 10000000;

  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    die("socket");
  }

  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &valid, sizeof(int));
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

  memset((char *) &si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(PORT);

  if (inet_aton(SERVER , &si_other.sin_addr) == 0) {
    fprintf(stderr, "inet_aton() failed\n");
    exit(1);
  }

  connexion(s, &si_other, slen);

  while(1) {
    printf("Enter message : ");
    gets(message);

    //send the message
    if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
      die("sendto()");
    }
    printf("Message envoyé: %s\n", message);

    //receive a reply and print it
    //clear the buffer by filling null, it might have previously received data
    memset(buf,'\0', BUFLEN);
    //try to receive some data, this is a blocking call
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1) {
      die("recvfrom()");
    }

    puts(buf);
  }

  close(s);
  return 0;
}
