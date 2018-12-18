# Manipulation de fichiers
# wget www.creatis.insa-lyon.fr/~kechichian/species-intro.txt

f = open("/home/rhidra/species-intro.txt") # Ouverture en lecture seule

contenu = f.read() # Ouverture totale du fichier (peut saturer la mémoire)
# Caractère EOF = '' => La chaîne vide
# En faisant f.read() à nouveau => Impossible de relire => la curseur est à la fin
f.close()

# Parcours du fichier
lines = list(f) # Liste de lignes du fichier
line = f.readlines() # Renvoie la ligne du curseur et avance dans le fichier

for line in f: # Itère sur les lignes. Méthode optimisée car ne charge pas en mémoire tout le fichier
    print(line, end='') # Retire le retour à la ligne à la fin

# Gestionnaire de contexte
with open(path) as f:
    for line as f:
        print(line, end='')
# En sortant du bloc de gestionnaire (with) => f.close() implicite
# Ouverture de ressources et pas besoin de se soucier de la fermeture de la ressource
# A utiliser tout le temps avec une ouverture de ressource

f.closed() # Renvoie un booléen
