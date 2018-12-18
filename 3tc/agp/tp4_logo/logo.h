/**
logo.h
Définit un arbre intermédiaire permettant de transcrire le programme logo en
une suite d'instructions. Celle-ci prend la forme d'un arbre.
Chaque noeud correspond à une instruction.
Chaque instruction pointe vers l'instruction suivante.
Elles peuvent aussi posséder un paramètre. Ce dernier est un nombre.
Ce nombre est une expression, définie dans expression.h.
*/

#ifndef _LOGO_H
#define _LOGO_H

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "expression.h"

// Définit les différents types d'instructions possibles
typedef enum node_type {
  FORWARD = 1,        // Le curseur avance
  LEFT = 2,           // Le curseur tourne à gauche
  RIGHT = 3,          // Le curseur tourne à droite
  REPEAT = 4,         // Répétition du bloc suivant
  COLOR = 5,          // Couleur du tracé
  SIZE = 6,           // Epaisseur du tracé
  SPLIT = 7,          // La section entre [] est exécutée indépendamment du reste
  STOP = 8,           // N'écrit plus
  START = 9,          // Recommence à écrire
  TOGGLE = 10,        // Ecrit ou n'écrit plus en fonction de l'état précédent
  BACKWARD = 11,      // Le curseur recule
  ORIGIN = 12,        // Le curseur retourne à l'origine
  PROC_DEF = 13,      // Définition d'une procédure secondaire
  PROC_CALL = 14,     // Appelle d'une procédure secondaire
  BG_COLOR = 15,      // Définit la couleur du fond
  LOOK_UP = 16,       // Le curseur pointe vers le haut
  LOOK_LEFT = 17,     // Le curseur pointe vers la gauche
  LOOK_RIGHT = 18,    // Le curseur pointe vers la droite
  LOOK_DOWN = 19      // Le curseur pointe vers le bas
} NODE_TYPE;

// Noeud d'une instruction
typedef struct noeud {
  // Type de l'instruction : FORWARD, LEFT, RIGHT, REPEAT, ...
  NODE_TYPE type;

  // Pointeur vers l'instruction suivante
  struct noeud *next;

  // Paramètre de l'instruction (dans "FORWARD a", 'a' est le paramètre)
  EXPR param;

  // Pointeur vers un programme à exécuter
  // Utile uniquement pour REPEAT et SPLIT
  struct noeud *prog;
} NODE;

typedef NODE *PROG;

// Génére un identifiant quasi unique pour chaque nom de fonction
int getStringHash(char* s);

// Ajoute l'instruction composée des paramètres suivant en haut du programme
PROG addInstrParam(PROG prog, NODE_TYPE type, EXPR param, PROG prog_repeat);

// Crée une instruction
NODE* createInstr(NODE_TYPE type, EXPR param, PROG prog_repeat);

// Ajoute une instruction en haut du programme
PROG addInstr(PROG prog, NODE *instr);

// Renvoie les instructions correspondants à la procédure
PROG procedure(PROG proc, double id);

// Libère l'arbre alloué en mémoire
void freeProg(PROG prog);

// Affiche le programme TC-LOGO
void affiche(PROG prog, PROG proc);

#endif
