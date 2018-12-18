#include <stdio.h>
#include <stdlib.h>

ARBRE ajouterABR(ARBRE a, int val) {
  NOEUD *pnoeud = (NOEUD*) malloc(sizeof(NOEUD));
  pnoeud->val = val;
  pnoeud->fg = NULL;
  pnoeud->fd = NULL;

  if (a->fg == NULL) {
    if (a->val >= val) {
      a->fg = pnoeud;
    }
  }

  if (a->fd == NULL) {
    if (a->val < val) {
      a->fd = pnoeud;
    }
  }

  if (a->fd->val < val) {
    ajouterABR()
  }
}
