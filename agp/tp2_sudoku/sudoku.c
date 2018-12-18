#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

int sudokuValide(int sudoku[9][9]) {
  int i, valide = 1;

  for (i = 0; i < 9; i++) {
    if (!suiteValide(sudoku[i]) || !suiteValide(getColonne(sudoku, i)) || !suiteValide(getRegion(sudoku, i))) 
      valide = 0;
  }

  return valide;
}

int suiteValide(int suite[9]) {
  int nbr[9] = {0,0,0,0,0,0,0,0,0};
  int i, valide = 1;

  for (i = 0; i < 9; i++) {
    if (suite[i] == 0)
      valide = 0;
    
    nbr[suite[i] - 1]++;
  }

  for (i = 0; i < 9; i++) {
    if (nbr[i] != 1) {
      valide = 0;
    }
  }

  return valide;
}

int* getColonne(int sudoku[9][9], int col) {
  int *colonne = (int *)malloc(9 * sizeof(int));
  int i;

  for (i = 0; i < 9; i++) {
    colonne[i] = sudoku[col][i];
  }

  return colonne;
}

int* getRegion(int sudoku[9][9], int reg) {
  int *region = (int *)malloc(9 * sizeof(int));
  int i, j, compteur = 0;
  int  iMin = (reg/3)*3, jMin = (reg%3)*3;

  for (i = iMin; i < iMin + 3; i++) {
    for (j = jMin; j < jMin + 3; j++) {
      region[compteur] = sudoku[i][j];
      compteur++;
    }
  }

  return region;
}

int resoudreSudoku(int sudoku[9][9]) {
  int interdictions[9][9][9];
  int *x, *y, *n;

  x = (int*)malloc(sizeof(int));
  y = (int*)malloc(sizeof(int));
  n = (int*)malloc(sizeof(int));

  initInterdictions(interdictions, sudoku);

  while (!sudokuPlein(sudoku)) {
    if (rechercheCase(interdictions, x, y, n)) {
      //printf("Ecriture dans la case (%d,%d) du chiffre %d ...\n", *x, *y, *n);
    } else {
      return 0;
    }

    sudoku[*x][*y] = *n;

    setInterdictions(interdictions, *x, *y, *n);
  }
  
  return 1;
}

int sudokuPlein(int sudoku[9][9]) {
  int i, j, plein = 1;
  
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (sudoku[i][j] == 0)
        plein = 0;
    }
  }

  return plein;
}

void initInterdictions(int interdictions[9][9][9], int sudoku[9][9]) {
  int i, j, k;

  // Initialisation à zéro du tableau des interdictions
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      for (k = 0; k < 9; k++) {
        interdictions[i][j][k] = 0;
      }
    }
  }

  // Mise en place des interdictions sur la grille
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (sudoku[i][j] != 0) {
        setInterdictions(interdictions, i, j, sudoku[i][j]);
      }
    }
  }
}

void setInterdictions(int interdictions[9][9][9], int x, int y, int n) {
  int i, j, regionX, regionY;

  // Règle pour la case (si elle est pleine, elle ne peut rien recevoir)
  for (i = 0; i < 9; i++) {
    interdictions[x][y][i] = 1;
  }

  // Règles des lignes et des colonnes
  for (i = 0; i < 9; i++) {
    interdictions[x][i][n-1] = 1;
    interdictions[i][y][n-1] = 1;
  }

  // Règles des régions
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      regionX = x/3;
      regionY = y/3;

      if (regionX*3 <= i && i < (regionX+1)*3 && regionY*3 <= j && j < (regionY+1)*3)
        interdictions[i][j][n-1] = 1;
    }
  }
}

int rechercheCase(int interdictions[9][9][9], int *x, int *y, int *n) {
  int i, j, k, compteurInterdictions, nbr, solvable = 0;

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      compteurInterdictions = 0;
      for (k = 0; k < 9; k++) {

        if (interdictions[i][j][k]) {
          compteurInterdictions++;
        } else {
          nbr = k+1;
        }
      }
      if (compteurInterdictions == 8) {
        *x = i;
        *y = j;
        *n = nbr;
        solvable = 1;
      }
    }
  }

  if (!solvable)
    return 0;
  else
    return 1;
} 
