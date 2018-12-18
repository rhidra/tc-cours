#include "pile.h"

int main() {
  int i;
  PILE pile = InitPile();

  for (i = 9; i > 0; i--) {
    Empiler(&pile, i);
  }

  printf("Affichage de la pile à l'adresse %p :\n", pile);
  afficherPile(pile);

  Depiler(&pile);
  Depiler(&pile);

  printf("Affichage de la pile après 2 dépilages :\n");
  afficherPile(pile);
}
