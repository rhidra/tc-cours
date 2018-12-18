#include <stdio.h>
#include <stdlib.h>

int *lireTabEntier(int N) {
  int i, val;

  // Allocation dynamique du tableau
  int* tab = (int*) malloc(sizeof(int)*N);

  // Saisie des données par l'utilisateur
  for (i = 0; i < N; i++) {
    printf("Rentrez un entier (%d/%d) : ", i+1, N);
    scanf("%d", &val);
    tab[i] = val;
  }
  printf("\n");

  // Affichage des données
  printf("Affichage du tableau ...\n");
  for (i = 0; i < N; i++) {
    printf("Entier n°%d : %d\n", i+1, tab[i]);
  }

  // Fin de la fonction
  return tab;
}

int main() {
  // Appel de la fonction
  int* tab = lireTabEntier(5);

  // Libération de la mémoire allouée
  free(tab);

  return 0;
}
