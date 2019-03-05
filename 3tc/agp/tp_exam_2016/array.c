#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void flattenArray(int tab[], int size) {
  int min = getMin(tab, size), i;

  for (i = 0; i < size; i++) {
    tab[i] = min;
  }
}

int getMin(int tab[], int size) {
  int min = tab[0], i;

  for (i = 0; i < size; i++) {
    if (tab[i] < min) {
      min = tab[i];
    }
  }

  return min;
}

void printArray(int tab[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    printf("tab[%d] = %d\n", i, tab[i]);
  }
}
