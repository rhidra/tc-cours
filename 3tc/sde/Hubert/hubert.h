#ifndef _HUBERT_H_
#define _HUBERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "include.h"
#include "resto.h"
#include "sem.h"
#include "shmem.h"

#define MAX_COURSIER 2
#define DELAI_MAX 10
#define DELAI_MIN 3

// Structure d'un coursier
typedef struct coursier {
  int pid_coursier;
  int pid_user;
  int etat; // 0 si le coursier dort (disponible), 1 sinon (occupé)
} COURSIER;

typedef struct resto {
  int type;
  int pid;
  int nb_plat;
} RESTO;

// Comportement du coursier
void coursier();

// Redirection du signal d'interruption d'un coursier
void fin_coursier();

// Boucle infinie de hubert
void hubert();

// Permet de réveiller un coursier pour un plat à aller chercher
void plat_ok();

// Permet de réveiller un coursier pour une commande annulée
void plat_annule();

// Redirection du signal d'interruption
void fin();

#endif
