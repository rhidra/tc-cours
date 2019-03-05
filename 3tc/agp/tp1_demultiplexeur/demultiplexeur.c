#include "demultiplexeur.h"

int main(int argc, char *argv[]) {
  char trame[TAILLE_MAX_TRAME];
  FILE* finput = NULL;
  FILE* f[NBR_FICHIERS];
  int i = 0;

  Stat stat;
  stat.trameTot = 0;
  stat.trameRej = 0;
  for(i = 0; i < NBR_FICHIERS; i++) {
    stat.octets[i] = 0;
  }

  // Ouverture des fichiers
  if (argc <= 1) {
    printf("Usage : demultiplexeur <Fichier de trames>\n");
    return 1;
  }

  if ((finput = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Erreur dans l'ouverture du fichier de trames !\n");
    exit(1);
  }

  for (i = 0; i < NBR_FICHIERS; i++) {
    char file[3] = {'f', '0'+i, '\0'};
    if ((f[i] = fopen(file, "w")) == NULL) {
      fprintf(stderr, "Erreur dans l'ouverture du fichier %s !\n", file);
      exit(1);
    }
  }

  // Lecture puis écriture des trames en paquets
  while(getTrame(finput, trame)) {
    stat.trameTot++;
    traiterTrame(trame, f, &stat);
  }

  // Fermeture des fichiers
  fclose(finput);
  for (i = 0; i < NBR_FICHIERS; i++) {
    fclose(f[i]);
  }

  // Affichage des stats
  printf("Ratio d'erreur : %d/%d = %f%%\n", stat.trameRej, stat.trameTot, (double)stat.trameRej/(double)stat.trameTot*100);
  for(i = 0; i < NBR_FICHIERS; i++) {
    printf("Nombre d'octets dans le fichier f%d : %d\n", i, stat.octets[i]);
  }

  return 0;
}

// Conversion d'une trame du fichier lu en un tableau
int getTrame(FILE* file, char* trame) {
  char c;
  int i = 0;

  while((c = fgetc(file)) != '\n' && c != EOF) {
    trame[i] = c;
    i++;
  }
  trame[i] = '\0';

  return !(c == EOF || trame[0] == '\0');
}

void traiterTrame(char* trame, FILE** f, Stat *stat) {
  if (checksum(trame)) {
    // Trame correcte
    writePacket(trame, f, stat);
  } else {
    // Trame incorrecte
    throwTrame(trame, f, stat);
  }
}

// Vérifie si le dernier caractère est bien le nombre de caractères de la trame en hexa
int checksum(char* trame) {
  int i = 1;

  while (trame[i+1] != '\0') {
    i++;
  }

  char end = trame[i];

  trame[i] = '\0';

  return (i-1)%16 == hexCharToInt(end);
}

// Convertie un caractère hexadécimal en entier décimal
int hexCharToInt(char d) {
  if (d >= '0' && d <= '9') {
    return d - '0';
  }
  d = tolower(d);
  if (d >= 'a' && d <= 'f') {
    return (d - 'a') + 10;
  }
  return -1;
}

// Ecrit une trame mauvaise dans le fichier poubelle et met à jour le nombre de trames jetées
void throwTrame(char* trame, FILE** f, Stat* stat) {
  int i = 1;

  while (trame[i] != '\0') {
    fputc(trame[i], f[0]);
    i++;
    stat->octets[0]++;
  } 

  stat->trameRej++;
  fputc('\n', f[0]);
}

// Ecrit la trame dans le bon fichier sous forme de paquets et met à jour les stats
void writePacket(char* trame, FILE** f, Stat* stat) {
  if (trame[0] > '5' || trame[0] < '1') {
    throwTrame(trame, f, stat);
    return;
  } 

  // Sélection du fichier output
  int output = trame[0] - '0';
  int i = 1;
  int taille = 0;

  // Calcul de la taille de la trame
  while(trame[i] != '\0') {
    taille++;
    i++;
  }

  if (taille == 0)
    return;

  // Complétion des octets manquants de la trame
  if (taille%7 != 0) {
    for(; i < (taille+1) + (7 - taille%7); i++) {
      trame[i] = '?';
    }
    trame[i] = '\0';
    taille += 7 - taille%7;
  }

  // Ecriture de la trame en plusieurs paquets de 7 octets
  int packet = 0;
  i = 1;
  int checksum = 0;

  for (packet
   = 0; packet < taille/7; packet++) {
    for (;i < 7 + packet*7+1; i++) {
      fputc(trame[i], f[output]);
      stat->octets[output]++;
      if (trame[i] != '?')
        checksum++;
    }

    // Ajout du checksum à la fin du paquet
    fputc(checksum + '0', f[output]);
    stat->octets[output]++;
    fputc('\n', f[output]);

    checksum = 0;
  }
}
