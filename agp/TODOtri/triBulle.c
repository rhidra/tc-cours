#include "triBulle.h"

void triBulle(int T[], int N)
{
  int permut, i;

  do {
    permut = 0;
    for (i = 0; i < N-1; i++) {
      if (T[i] > T[i+1]) {
        echanger(T, i, i+1);
        permut = 1;
      }
    }
  } while (permut);
}

void echanger(int T[], int a, int b) {
  int m = T[a];
  T[a] = T[b];
  T[b] = m;
}
