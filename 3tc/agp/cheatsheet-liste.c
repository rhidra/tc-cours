struct elem {
  int elem;
  struct elem *next;
};

typedef struct elem ELEMLISTE;
typedef ELEMLISTE *LISTE;

void addListe(LISTE *list, int val); // Ajoute la valeur au sommet de la LISTE
LISTE createListe(int val); // Crée la liste avec la première valeur
void removeListe(LISTE *list); // Supprime le premier élément
void viderListe(LISTE *list);




// Ajoute la valeur dans une lise triée
void addListe(LISTE *list, int val) {
  if (*list == NULL || (*list)->elem <= val) {
    ELEMLISTE *elem = (ELEMLISTE*) malloc(sizeof(ELEMLISTE));
    elem->elem = val;
    elem->next = *list;
    *list = elem;
  } else {
    addListe(&(*list)->next, val);
  }
}

// Ajoute la valeur juste au sommet de la liste
void addListe(LISTE *list, int val) {
  ELEMLISTE *elem = (ELEMLISTE*) malloc(sizeof(ELEMLISTE));
  elem->elem = val;
  elem->next = *list;
  *list = elem;
}

LISTE createListe(int val) {
  LISTE list = NULL;
  addListe(&list, val);
  return list;
}
