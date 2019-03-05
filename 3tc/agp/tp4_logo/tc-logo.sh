#!/bin/sh
# tc-logo.sh
# Script permettant de faciliter l'utilisation du programme tc-logo,
# notamment sur l'utilisation sur un groupe de fichier.
# Usage: tc-logo.sh <file1.logo> [ <file2.logo> ... ]

# Ce programme utilise feh pour la visualisation des fichiers SVG.

# Exécute le programme tc-logo avec le fichier en flux d'entrée
# et affiche le flux de sortie.
exec_logo() {
  echo "\nExécution de tc-logo pour $1 ..."
  ./tc-logo < $1 > tmp.svg
  if [ $? = 0 ]; then
    echo "Affichage du fichier SVG ..."
    # Modifiez la ligne suivante si feh n'est pas installé sur votre machine
    feh --magick-timeout 10 tmp.svg
    rm tmp.svg
  else
    echo "Erreur dans l'exécution de tc-logo !"
  fi
}

# Vérification pour l'exécution correcte du programme
if [ $# = 0 ]; then
  echo "Usage: tc-logo.sh <file1.logo> [ <file2.logo> ... ]"
elif [ ! -x ./tc-logo ]; then
  echo "./tc-logo does not exist !"
  echo "Try compiling the tc-logo program with 'make'"
  exit
fi

# Exécute le programme tc-logo sur tous les fichiers passés en paramètre
for i
do
  if [ -e $i ]; then
    exec_logo $i
  else
    echo "$i does not exist !"
  fi
done
