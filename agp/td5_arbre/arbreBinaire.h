#ifndef ARBRE_BINAIRE_H_
#define ARBRE_BINAIRE_H_

#include <stdlib.h>
#include <stdio.h>

struct node{
	int val;
	struct node *filsGauche;
	struct node *filsDroit;
};

typedef struct node NODE;
typedef NODE* ARBRE;

ARBRE createArbre(int val, ARBRE fg, ARBRE fd);
int hauteurArbre(ARBRE arbre);

#endif