#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include "include.h"
#include "sem.h"
#include "shmem.h"
#include "resto.h"

void fin_user();

void commande_prete();

void commande_impossible();

#endif
