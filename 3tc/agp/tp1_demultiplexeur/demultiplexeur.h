#ifndef DEMULTIPLEXEUR_H_
#define DEMULTIPLEXEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TAILLE_MAX_TRAME 70
#define NBR_FICHIERS 6

/**
 * Structure permettant de stocker les informations relatives aux statistiques.
 */
typedef struct Stat Stat;
struct Stat {
	int trameTot;
	int trameRej;
	int octets[NBR_FICHIERS];
};

int getTrame(FILE*, char*);
void traiterTrame(char*, FILE**, Stat*);
int checksum(char*); //Retire le dernier caractère
void throwTrame(char*, FILE**, Stat*);
void writePacket(char*, FILE**, Stat*);
int hexCharToInt(char);

#endif