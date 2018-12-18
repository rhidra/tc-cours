#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <time.h>

#include "config.h"

int semCoiffeur;
int semMutex;
int semClient;


int P(int id) {
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = -1;
  op.sem_flg = 0;
  return semop(id, &op, 1);
}

int V(int id) {
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = 1;
  op.sem_flg = 0;
  return semop(id, &op, 1);
}

void Couper_Cheveux() {
  printf("Le client se fait couper les cheveux ... \n");
  sleep(15);
}

void fin() {
  printf("FIN\n");
  semctl(semCoiffeur, 0, IPC_RMID);
  semctl(semClient, 0, IPC_RMID);
  semctl(semMutex, 0, IPC_RMID);
  exit(0);
}

int main() {
  srand(time(NULL));
  semCoiffeur = semget(CLE_COIFFEUR, 1, 0660 | IPC_CREAT);
  semClient = semget(CLE_CLIENT, 1, 0660 | IPC_CREAT | IPC_NOWAIT);
  semMutex = semget(CLE_MUTEX, 1, 0660 | IPC_CREAT);
  semctl(semCoiffeur, 0, SETVAL, 0);
  semctl(semClient, 0, SETVAL, MAX_CLIENTS);
  semctl(semMutex, 0, SETVAL, 1);

  signal(SIGINT, fin);

  while (1) {
    printf("Le coiffeur s'assoie dans le fauteuil et s'endort ...\n");
    // delay(rand()%5);

    P(semCoiffeur);

    printf("Le coiffeur se réveille et quitte le fauteuil !\n");

    Couper_Cheveux();
  }

  return 0;
}
