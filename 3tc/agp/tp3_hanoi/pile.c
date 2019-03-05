#include "pile.h"

int error1(char *message) {
  printf("Erreur : %s !\n", message);
  exit(-1);
}

PILE InitPile() {
  return NULL;
}

int Empiler(PILE* ppile, int elem) {
  ELEMPILE *pelem = (ELEMPILE*) malloc(sizeof(ELEMPILE));
  if (pelem == NULL)
    error1("Allocation mémoire à l'empilage impossible");

  pelem->elem = elem;
  pelem->suivant = (*ppile);

  *ppile = pelem;

  return 0;
}

int Depiler(PILE *ppile) {
  if (ppile == NULL || *ppile == NULL)
    error1("Pile vide à dépiler");

  PILE temp = *ppile;
  int val = temp->elem;
  (*ppile) = temp->suivant;
  free(temp);

  return val;
}

void afficherPile(PILE pile) {
  ELEMPILE *pelem = pile;
  int i = 0;

  while (pelem != NULL) {
    printf("Element %d : %d\n", i, pelem->elem);
    i++;
    pelem = pelem->suivant;
  }

  printf("\n");
}

void afficherHanoi(PILE pile1, PILE pile2, PILE pile3, int N) {
  int i, taille1 = getPileSize(pile1), taille2 = getPileSize(pile2);
  int taille3 = getPileSize(pile3);

  for (i = 0; i < N; i++) {
    // Pile 1
    if (i >= N-taille1) {
      printSymbol(N - pile1->elem, ' ');
      printSymbol(pile1->elem, '*');
      printf("|");
      printSymbol(pile1->elem, '*');
      printSymbol(N - pile1->elem, ' ');

      pile1 = pile1->suivant;
    } else {
      printSymbol(N, ' ');
      printf("|");
      printSymbol(N, ' ');
    }

    printf(" + ");

    // Pile 2
    if (i >= N-taille2) {
      printSymbol(N - pile2->elem, ' ');
      printSymbol(pile2->elem, '*');
      printf("|");
      printSymbol(pile2->elem, '*');
      printSymbol(N - pile2->elem, ' ');

      pile2 = pile2->suivant;
    } else {
      printSymbol(N, ' ');
      printf("|");
      printSymbol(N, ' ');
    }

    printf(" + ");

    // Pile 3
    if (i >= N-taille3) {
      printSymbol(N - pile3->elem, ' ');
      printSymbol(pile3->elem, '*');
      printf("|");
      printSymbol(pile3->elem, '*');
      printSymbol(N - pile3->elem, ' ');

      pile3 = pile3->suivant;
    } else {
      printSymbol(N, ' ');
      printf("|");
      printSymbol(N, ' ');
    }
    printf("\n");
  }
  printSymbol(N*2+1, '=');
  printf(" + ");
  printSymbol(N*2+1, '=');
  printf(" + ");
  printSymbol(N*2+1, '=');
  printf("\n\n");
}

int getPileSize(PILE pile) {
  int i = 0;

  while (pile != NULL) {
    i++;
    pile = pile->suivant;
  }

  return i;
}

void printSymbol(int n, char c) {
  int i;

  for (i = 0; i < n; i++) {
    printf("%c", c);
  }
}
