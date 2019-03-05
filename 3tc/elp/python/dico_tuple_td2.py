# Tuple
t = ( )
type(t) # t = tuple
# Tuple sont pas modifiables => Sera toujours constitué de 3 composants

t=("raz", None, 3.13)
t[2] # = 3.13

# On ne peut pas modifier le composant d'un tuple, sauf s'il est muable

a, b = t # a=t[0]; b=t[1] affectation multiple

for i, f in enumerate(fruits): # Affectation multiple du retour de enumerate()
    print(i, f) # Enumerate ne renvoie pas un ensemble d'éléments, mais plutôt un tuple avec l'index et l'élément

for t in enumerate(fruits):
    print(t) # t est alors un tuple de taille 2


# Dictionnaire
# Suite de paires (clé, valeur), table associative

# Les clés sont immuables
# Les éléments ne sont pas triés dans un Dictionnaire (pas comme en C++)

d = {} # Dictionnaire vide
d = { "raz":1982, "toi":1997, "guido":1956 } # { clé:valeur }
d = dict( [ ("x", 9), ("y", 10), ("z", 11) ] ) # Contructeur avec une liste de tuples
d = dict(x=9, y=10, z=11) # Convertit x, y, z en chaine de caractères

d["x"] = 10
del d["x"]

# Itération sur une clé
for k in d:
    print(k) # Affiche les clés
    print(k, d[k]) # Affiche clés et valeurs

# Itération sur un tuple (clé, valeur)
for k, v in d.items():
    print(k, v) # Affiche clés et valeurs

# Test de présence d'éléments
"x" in d # Renvoie un booléen
