#include "hanoi.h"

int deplacer(PILE *source, PILE *dest) {
  int val = Depiler(source);

  if (*dest == NULL) {
    Empiler(dest, val);
  } else if ((*dest)->elem >= val) {
    Empiler(dest, val);
  } else {
    error1("Problème d'empilement");
    return 1;
  }

  return 0;
}

int hanoi(PILE *depart, PILE *passage, PILE *arrivee, int N) {
  afficherHanoi(depart, passage, arrivee);
  if (*depart == NULL) {
    error1("Pile de départ vide");

    return 1;
  } else if (N == 1) {
    deplacer(depart, arrivee);
  } else {
    hanoi(depart, arrivee, passage, N-1);
    deplacer(depart, arrivee);
    hanoi(passage, depart, arrivee, N-1);
  }

  return 0;
}
