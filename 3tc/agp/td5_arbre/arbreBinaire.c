#include "arbreBinaire.h"

ARBRE createArbre(int val, ARBRE fg, ARBRE fd) {
	ARBRE temp;
	temp = (ARBRE) malloc(sizeof(NODE));

	if (temp == NULL)
		return NULL;

	temp->val = val;
	temp->filsGauche = fg;
	temp->filsDroit = fd;
	return temp;
}

int hauteurArbre(ARBRE arbre) {
	int hg = 0, hd = 0;

	if (arbre == NULL)
		return 0;

	if (arbre->filsGauche == NULL && arbre->filsDroit == NULL) {
		return 0;
	} else {
		if (arbre->filsGauche != NULL)
			hg = hauteurArbre(arbre->filsGauche);
		if (arbre->filsDroit != NULL)
			hd = hauteurArbre(arbre->filsDroit);

		return (hg > hd) ? hg : hd + 1;
	}
}

int estEquilibre(ARBRE arbre) {
	if (arbre == NULL)
		return 1;
	else {
		if (abs(hauteurArbre(arbre->filsGauche) - hauteurArbre(arbre->filsDroit)) <= 1) {
			return estEquilibre(arbre->filsGauche) && estEquilibre(arbre->filsDroit);
		} else {
			return 0;
		}
	}
}