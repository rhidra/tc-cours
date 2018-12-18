#ifndef _LIST_H_
#define _LIST_H_

typedef struct cell {
  int val;
  struct cell *suivant;
  struct cell *precedent;
} CELL;
typedef CELL *LIST;

LIST insertionLDC_triee(LIST liste, int valeur);
void afficherLDC(LIST liste);
void libererLDC(LIST liste);

#endif
