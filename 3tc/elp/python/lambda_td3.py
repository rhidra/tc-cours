# Expression Lambda

def f(n):
    def g(x):
        return x + n
    return g # Fonctionne car g est un objet
f4 = f(4)
f4(5) # Appelle la fonction g

# OU alors :
def f(n):
    return lambda x: x + n # Définition d'une fonction sans nom
f6 = f(6)
f6(10) # Affiche 16

# Autre exemple
phrase = "Mary had a little lamb"
words = phrase.split()
sorted(words) # Mots triés en tenant compte de la casse
# On cherche à ne pas tenir compte de la casse
sorted(words, key=lambda w: w.lower()) # Key est évalué à chaque itération

# Lambda permet de ne pas avoir à définir une fonction avec un nom à chaque fois

# Trier un dico en fonction des valeurs et pas des clés (comportement par défaut)
d = { "raz":1982, "toi":1997, "guido":1956 }
sorted(d.items(), key=lambda t: t[1])
