#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
  printf("Signal d'interruption pour le process : %d\n", getpid());
  exit(0);
}

int main() {
  int pid;

  printf("Début\n");

  pid = fork();

  if (pid == 0) { // Fils
    signal(SIGINT, handler);
    while (1) {
      printf("Je suis le fils (%d) !\n", getpid());
      sleep(2);
    }
  } else if (pid > 0) { // Père
    signal(SIGINT, handler);
    while (1) {
      printf("Je suis le père (%d) !\n", getpid());
      sleep(2);
    }
  }

  return 0;
}
