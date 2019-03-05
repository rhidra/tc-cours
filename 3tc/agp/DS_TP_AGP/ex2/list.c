#include <stdio.h>
#include <stdlib.h>
#include "list.h"

LIST insertionLDC_triee(LIST liste, int valeur) {
  if (liste == NULL) {
    // Si la liste est vide, ou si on a atteint le bout
    CELL *elem = (CELL*) malloc(sizeof(CELL));
    elem->val = valeur;
    elem->suivant = NULL;
    elem->precedent = NULL;

    return elem;
  } else if (liste->val > valeur) {
    // Si l'élément doit être inséré avant l'élément de la liste pointé ...
    CELL *elem = (CELL*) malloc(sizeof(CELL));
    elem->val = valeur;
    elem->suivant = liste;
    elem->precedent == NULL;

    liste->precedent = elem;

    return elem;

  } else {
    // Sinon, on continue de parcourir récursivement la liste
    liste->suivant = insertionLDC_triee(liste->suivant, valeur);
    liste->suivant->precedent = liste;
    return liste;
  }
}

void afficherLDC(LIST liste) {
  if (liste != NULL) {
    printf("Valeur : %d\n", liste->val);
    afficherLDC(liste->suivant);
  }
}

void libererLDC(LIST liste) {
  LIST temp;

  while (liste != NULL) {
    temp = liste;
    liste = liste->suivant;
    free(temp);
  }
}
