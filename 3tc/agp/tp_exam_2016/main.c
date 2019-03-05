#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main() {
  int tab[] = {2,3,4,6,7,8,9};
  int size = 7;

  printf("Avant flattenArray() : \n");
  printArray(tab, size);

  flattenArray(tab, size);

  printf("Avant flattenArray() : \n");
  printArray(tab, size);

  return 0;
}
