#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_alarm(int sig) {
  if (sig == SIGALRM) {
    printf("Signal reçue (pid=%d)\n", getpid());
  }
}

void sleep2(int n) {
  signal(SIGALRM, signal_alarm);
  alarm(n);
  pause();
}

int main() {
  printf("Début (pid=%d)\n", getpid());
  sleep2(3);
  printf("Fin (pid=%d)\n", getpid());
}
