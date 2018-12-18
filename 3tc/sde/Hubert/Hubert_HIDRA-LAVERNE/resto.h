#ifndef _RESTO_H_
#define _RESTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include "include.h"
#include "sem.h"
#include "shmem.h"

#define CHINOIS 1
#define ITALIEN 2
#define FASTFOOD 3

#define NB_RESTO 3

#define NOMBRE_PLAT_CHINOIS 3
#define NOMBRE_PLAT_ITALIEN 3
#define NOMBRE_PLAT_FASTFOOD 4

//Structure d'un plat
typedef struct plat {
	int id_plat;
	int quantite;
	char nom_plat[10];
} PLAT;

void fin_cuisine();
void fin_resto();
void commande_prete();
void commande_impossible();
void init_shmem(int type_resto, PLAT* addr_shmem, int id_sem);

#endif
