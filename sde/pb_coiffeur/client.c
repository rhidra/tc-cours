#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#include "config.h"

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

void Obtenir_Coupe() {
  printf("Le client est en train de se faire couper les cheveux ...\n");
  sleep(15);
}

int main() {
  srand(time(NULL));
  int semCoiffeur = semget(CLE_COIFFEUR, 1, 0660);
  int semClient = semget(CLE_CLIENT, 1, 0660);
  int semMutex = semget(CLE_MUTEX, 1, 0660);


  P(semClient);
  printf("Un nouveau client rentre chez le coiffeur ...\n");
  printf("Le client va dans la file d'attente ...\n");

  P(semMutex);

  V(semClient);

  printf("Le client sort de la file d'attente.\n");

  V(semCoiffeur);

  printf("Un client s'assoie dans le fauteuil !\n");

  Obtenir_Coupe();

  printf("Le client quitte le fauteuil !\n");

  V(semMutex);

  printf("Le client s'en va.\n");

  return 0;
}
