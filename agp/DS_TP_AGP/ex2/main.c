#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
  LIST liste = NULL;
  int i, val;

  for (i = 0; i < 5; i++) {
    printf("Rentrez un nombre : ");
    scanf("%d", &val);
    liste = insertionLDC_triee(liste, val);
  }

  printf("\n");

  printf("Les valeurs de la liste sont :\n");
  afficherLDC(liste);

  libererLDC(liste);

  return 0;
}
