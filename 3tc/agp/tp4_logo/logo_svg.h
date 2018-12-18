/**
logo_svg.h
Définit l'ensemble des fonctions utiles, afin de transformer un arbre de programme
TC-LOGO en un fichier SVG. Adapte les dimensions de l'image en fonction de la
taille définit par le programme TC-LOGO.
Gère les différentes couleurs proposées.
*/

#ifndef _LOGO_SVG_H
#define _LOGO_SVG_H

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "logo.h"

// Constantes utiles pour des conversions
#define PI 3.14159265
#define DEG_TO_RAD 0.017453292500000002

// Nombre de pixels de marge entre la bordure de l'image et le dessin
#define MARGE 500

// Structure pour la couleur du stylo
typedef struct color {
  // Quantité de rouge (de 0 à 255)
  int r;

  // Quantité de vert (de 0 à 255)
  int v;

  // Quantité de bleu (de 0 à 255)
  int b;
} RGB_COLOR;

// Convertit une couleur hexadécimale en struct COLOR
// Format de la couleur : c = B * 65536 + G * 256 + R
RGB_COLOR getColor(int c);

// COULEURS
#define RED 255
#define GREEN 65280
#define BLUE 16711680
#define MAGENTA 16711935
#define CYAN 16776960
#define YELLOW 65535
#define BLACK 0
#define WHITE 16777215
#define GRAY 8388607

// Structure du curseur utilisé pour dessiner
typedef struct stylo {
  // La position du stylo
  double x;
  double y;

  // L'angle du stylo, en degré
  double angle;

  // La couleur du stylo
  RGB_COLOR color;

  // L'épaisseur du trait
  int strokeWidth;

  // En train de tracer ?
  int bTracing;
} STYLO;

typedef struct stylo *PEN;

// Structure pour les conditions initiales de l'image
typedef struct imageInit {
  // Position initiale du curseur par rapport à une origine déplacée
  double originx;
  double originy;

  // Largeur et longueur de l'image
  double width;
  double height;

  // Positions maximales par rapport à l'origine
  double maxx;
  double minx;
  double maxy;
  double miny;

  // Couleur du fond de l'image
  RGB_COLOR background;
} IMAGE_INFO;

// Crée un stylo
PEN createPen();

// Ecrit le contenu du fichier SVG à partir de l'arbre d'un programme TC-LOGO
void makeSVG(PROG prog);

// Récupère les conditions intiales de l'image avant de commencer à tracer
IMAGE_INFO *getImageInfo(PROG prog);
void getImageInfo_recursive(PROG prog, PROG proc, PEN pen, IMAGE_INFO *info);

// Construit le fichier SVG récursivement
// proc contient le programme complet afin de retrouver les appels de procédures
void svg(PROG prog, PROG proc, PEN pen, IMAGE_INFO *info);

// Déplace le stylo devant et inscrit dans la sortie la ligne SVG
void moveForward(PEN pen, double val);

// Tourne le stylo
void rotate(PEN pen, double val);

#endif
