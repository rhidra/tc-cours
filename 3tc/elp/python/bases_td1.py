#### Help
# Langage autodocumenté => doc écrite dans la définition de la fonction
abs?
help(abs)

id(x) #Donne identifiant objet
y=x #id(y) = id(x) => modification de x = modification de y
#Toutes les variables, fonctions, objets sont des références
#Certains objets peuvent être modifiés, d autres non = immuables
#Si on modifie un objet immuable (int, double, numeric) => id change (nouvel objet créé)
#Inverse avec un objet muable (modification avec les méthodes sur l objet)

x is y # <=> id(x) == id(y) # Les deux objets sont-ils identiques

# Opérations
x ** 4 #Puissance
4 / 6 #=0.666 => Division par virgule flotante
4 //6 #=0 => Division entière

_ # Valeur de la dernière expression évaluée

# Conditions
a < b == c # <=> (a < b) and c

### Structures de données
## Séquence :
v = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]         # Liste
printf("This is a list", v)
len(v)                      # Longueur de la séquence
3 in v                      # Présence de l élément dans la liste
3 not in v
v[0]                        # Indexation
v[1:4]                      # Plage de valeur [1, 4[ (slicing)
v[:4]                       # Début de la liste sous-entendu (ou fin avec v[1:])
v[1:7:2]                    # Notion de pas [begin:end(non-inclu):pas]
v[-1]                       # Désigne l élément final (boucle dans les négatifs)
v[100] # IMPOSSIBLE (ne boucle pas dans l autre sens)
v[::-1]                     # Inverse la liste

for e in v:                 # Il faut que v supporte l itération
    print(e)

[1,2,3] + [4,5,6.666]       # Pour des opérandes de même type (liste ici) "+" = concaténation

## Chaîne de caractères :
d = r"c:\my\name"       # Définit une chaîne de caractère brute => N'échappe rien
d = """\
Hello !
"""
dir(d)                  # Permet de voir les méthodes associées à un objet
# Chaînes de caractère = IMMUABLE !!!!
# Impossible de faire une affectation !! => s[1] = 'a' => Ne fonctionne pas !

## Listes :
# Tableau dynamique qui stocke n importe quel type
# Optimisé pour l affectation et l indexation
range(1, 10)            # Crée itérateur entre le range (intervalle semi-ouert à droite)
v.insert(1, 500)        # Insert à la case n°1
v.extend([100, 200])    # Concatène

# List comprehension : Optimisé pour les listes
v = [expr for if for if ...]        # Met à jour la valeur de expr à chaque itération de ce qui suit
# Exemples :
v = [e ** 2 for e in range (11)]    # Carré des entiers usqu'à 10

v = [-2, -1, 0, 1, 2]
vp = [value for value in v if value >= 0]   # Filtre les valeurs négatives de v

v = ["apples", "oranges", "kiwis"]
vu = [fruit.upper() for fruit in v]         # Met v en majuscule

# Tableau 2D
m = [[1,2,3],
    [4,5,6],
    [7,8,9]]
mf = [e for row in m for e in row]          # Applati m (élimine les listes intermédiaires)
mt = [[row[i] for row in m] for i in range(3)]  # Transpose la matrice m

## NoneType
n = None                        # Type null
v = ["raz", "", None]
for s in v:
    if s: # <=> len(s) != 0
        print(s)                # "raz"
    elif s is None:
        print("got nothing !")  # None
    else:
        print("Empty sequence") # ""

def f():
    pass        # pass = permet de passer sans rien exécuter

for e in v[:]: # Permet d itérer sur une copie => a faire l orsqu on altere la structure de l itération

v[1:4] = []     # Permet de supprimer les index 1 à 4 (non-inclu)

del f           # Supprime la définition de la fonction f

for i, f in enumerate(v):   #"i, f" Définit un tuple
    print(i, f)     # Affiche index et element

for t in zip(v, p):     # Itère sur les deux listes en même temps, t est un tuple
    print(t)
