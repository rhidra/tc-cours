# Fonction

# Fonction = objet
# Contrairement au C, où une fonction est un pointeur "magique"

def f():
    pass

# Intégration dynamique de la fonction

def f():
    """Function f() -> None

    Do nothing
    """
    pass
help(f) # Affiche la fonction

# Type de renvoie si pas de retour => None

def f(aa, vv, uu):
    aa = 4
    vv.append(666)
    uu = [42, 1982]

f(4, [8, 9], [4])
# 1er argument = Pas modifié après l'appel
# 2ème argument = Modifié
# 3ème argument = Pas modifié
# Paramètres = variables locales pour la fonction initialisés à la valeur donné en argument

# Paramètres par défaut
def f(a = 10, b = 20):
    return a + b
f(5) # a = 5; b = 20
f(b = 5) # a = 10; b = 5

# Nombre de paramètres arbitraire
def f(name, *args):
    print(name)
    print(args) # args est un tuple avec tous les arguments supplémentaires

# Un exemple
def f(*args, sep = "/"):
    return sep.join(args)
f("usr", "local", "share") # Renvoie "usr/local/share"
reps = ["usr", "local", "share"]
# f(reps) ne fonctionne pas car reps est une liste
f(*reps) # Convertit la liste en tuple => Ne fonctionne que dans le contexte d'un appel de fonction

# Nombre de paramètres spécifiés par mots-clé
def f(name, *args, **kwargs): # kwargs est un dictionnaire
    print(name)
    print(args) # args est un tuple
    print(kwargs) # kwargs est un dico
f("name", 0,1,2,3, x=1, y=2, z=3) # 0,1,2,3 sont dans args; x,y,z sont dans kwargs

# Paramètre par défaut avancés
x = 6
def f(a = x): # Le paramètre x est évalué une seule fois pour donner la valeur par défaut de la fonction f()
    print(x)
f() # Affiche 6
x = 8
f() # Affiche 6
