#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int enPause = 0;
int enCours = 1;
int sec = 0;

void reinit() {
  printf("Réinitialisation du chrono\n");
  sec = 0;
  printf("Chrono : %ds\n", sec);
}

void arret() {
  printf("Arret du chrono\n");
  enPause = !enPause;
}

void stop() {
  printf("Fin du chrono\n");
  enCours = 0;
}

int main() {
  printf("r:réinitialisation; a:arrêt; s:stop\n");
  int pid = fork();

  if (pid != 0) {
    // Processus père
    char input;
    while (input != 's') {
      scanf("%c", &input);

      switch(input) {
        case 'r':
          kill(pid, SIGUSR1);
          break;
        case 'a':
          kill(pid, SIGUSR2);
          break;
        case 's':
          kill(pid, SIGINT);
          break;
        default:
          break;
      }
    }
  } else {
    // Processus fils
    signal(SIGUSR1, reinit);
    signal(SIGUSR2, arret);
    signal(SIGINT, stop);

    sec = 0;
    while(enCours) {
      if (!enPause) {
        printf("Chrono : %ds\n", sec);
        sec++;
        sleep(1);
      }
    }
  }

  return 0;
}
