/**
expression.h
Définit une expression.
Permet de caractériser un nombre grâce à une opération mathématique.
L'opération peut être une somme, une multiplication, une soustraction
ou une division. Il est aussi possible de spécifier des nombres spéciaux,
comme des nombres aléatoires. Il est aussi possible de définir la
valeur maximale que peut prendre un nombre aléatoire.
*/

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

// Includes
#include <stdio.h>
#include <stdlib.h>

// Constantes pour le choix d'un nombre aléatoire par défaut
#define MAX_RAND 500
#define MIN_RAND 1

// Type pour un noeud d'expression
typedef enum expr_type {
  ADD = 1,
  MULT = 2,
  SUB = 3,
  DIV = 4,
  RANDOM = 5,
  EXPR_ENTIER = 6
} EXPR_TYPE;

// Noeud d'un arbre d'expression
typedef struct expression{
  // Type de l'expression
  EXPR_TYPE type;

  // Paramètre si type == ENTIER
  double param;

  // Enfant gauche et droit
  struct expression *nextl;
  struct expression *nextr;
} expr;

typedef expr *EXPR;

// Renvoie la valeur de l'expression
double getExprValue(EXPR expr);

// Crée un noeud d'expression, sans enfant
EXPR createExpr(EXPR_TYPE type, double param);

// Ajoute l'expression à la feuille parent
EXPR addExpr(EXPR parent, EXPR nextl, EXPR nextr);

// Libération de l'arbre en mémoire
void freeExpr(EXPR expr);

#endif
