# Modules dans python

# De ce dossier, on a un fichier fibonacci.py

import fibonacci

# On peut alors accéder aux fonctions du module (fib1 et fib2)
fibonacci.fib1(5)

# Importation d'une fonction
from fibonacci import fib2

# Exécution en mode interactif
%run fibonacci # Exécute le main du module
fibonacci.__name__ # Renvoie "fibonacci" car ce n'est pas le main

# Rechargement du module en séance interactive
import importlib
importlib.reload(fibonacci)

# Path
# Regarde dans sys.path et dans le répertoire courant
import sys
sys.path
# peut être dans $HOME/.local/lib/python3.6/sites-packages
# juste besoin de déplacer le .py dans ce répertoire
# Le module déjà importé est builtins et contient toutes les fonctions de base

# Module os
# Permet interfaçage avec l'OS, alternative aux script shell
