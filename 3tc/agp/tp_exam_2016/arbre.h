#ifndef _ARBRE_H
#define _ARBRE_H

typedef struct noeud {
  int val;
  struct noeud *fd;
  struct noeud *fg;
} NOEUD;
typedef NOEUD *ARBRE;

#endif
