#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int pid = 0;

void signal_handle() {
    printf("Le père vient de se réveiller !\n");
    kill(pid, SIGKILL);
}

int main() {
  pid = fork();
  if (pid != 0) {
    // Processus père
    printf("Le père s'endort ...\n");
    signal(SIGUSR1, signal_handle);

    pause();

  } else {
    // Processus fils
    printf("Le fils vient d'être créé !\n");

    sleep(5);

    kill(getppid(), SIGUSR1);

    while(1) {
      printf("Le fils est réveillé\n");
      sleep(1);
    }
  }

  return 0;
}
