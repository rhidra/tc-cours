#include <stdio.h>
#include <stdlib.h>
#include "arbreBinaire.h"

int main() {
	ARBRE fils1 = createArbre(1, NULL, NULL);
	ARBRE fils2 = createArbre(2, NULL, NULL);

	ARBRE fils3 = createArbre(3, fils1, fils2);
	ARBRE fils4 = createArbre(4, NULL, NULL);

	ARBRE fils5 = createArbre(5, fils4, fils3);

	ARBRE fils6 = createArbre(6, NULL, NULL);

	ARBRE root = createArbre(0, fils5, fils6);

	printf("Hauteur de l'arbre : %d\n", hauteurArbre(root));
}