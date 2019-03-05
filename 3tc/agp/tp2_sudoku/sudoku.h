
/**
 * Vérifie si la grille de sudoku est correcte.
 *
 * @return 1 si la grille est valide. 0 sinon.
 */
int sudokuValide(int[9][9]);

/**
 * Vérifie si la suite de 9 nombres est une séquence valide de sudoku.
 * Par exemple, si c'est une ligne de la grille valide.
 *
 * @return 1 si la suite est valide. 0 sinon.
 */
int suiteValide(int[9]);

/**
 * Renvoie la colonne de la grille.
 *
 * @return Pointeur vers un tableau de la colonne de la grille.
 */
int* getColonne(int[9][9], int);

/**
 * Renvoie la région (groupe de neuf cases qui n'est pas une ligne ou une colonne)
 * correspondant à l'index entré.
 * Index de 0 à 8.
 *
 * @return Pointeur vers un tableau de la région de la grille dans un ordre arbitraire.
 */
int* getRegion(int[9][9], int);

/**
 * Résout un sudoku simple.
 *
 * @return 0 si le sudoku est irrésolvable (non simple).
 */
int resoudreSudoku(int[9][9]);

/**
 * Vérifie si le sudoku est plein.
 *
 * @return 1 si la grille est pleine. 0 sinon.
 */
int sudokuPlein(int[9][9]);

/**
 * Initialise la matrice des interdictions aux valeurs correspondants
 * à la grille de sudoku passée en paramètre.
 */
void initInterdictions(int[9][9][9], int[9][9]);

/**
 * Ajoute à la matrice d'interdictions les interdictions 
 * provoquées par l'ajout d'une nouvelle case à la grille.
 */
void setInterdictions(int[9][9][9], int, int, int);

/**
 * Recherche la dernière case aillant qu'une seule possibilité de valeur.
 * C'est à dire, la case ayant huit contraintes dans la 
 * matrice d'interdictions.
 *
 * @return 0 s'il n'y a pas de case possible.
 */
int rechercheCase(int[9][9][9], int*, int*, int*);


