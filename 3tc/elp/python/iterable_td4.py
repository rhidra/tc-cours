# Iterable

# Dans une boucle
for e in v:
    print e
# On a ça :
it = iter(v) # On récupère un itérateur sur v
type(it) # list_iterator : permet de récupérer les éléments de v
next(it) # Permet de passer à l'élément suivant de la liste reliée à la liste


# Dans un objet, on a une méthode spéciale __iter__() qui renvoie l'iterateur

# Un itérateur qui renvoie les éléments de la suite de fibonacci
# On définit l'itérateur et l'objet à itérer dans le même objet
class FibIter:
    def __init__(self, n):
        self.n = n # Borne supérieure
        self.a, self.b = 0, 1 # Etat initial de la suite
    def __next__(self):
        # Méthode appelée par next(it)
        self.a, self.b = self.b, self.a + self.b
        if self.b < self.n:
            return self.b
        else:
            raise StopIteration()
    def __iter__(self):
        # Renvoie l'itérateur, c'est à dire l'objet,
        # car l'objet est à la fois itérateur et objet
        return self

f = FibIter(10)
it = iter(f)
next(it) # 1
next(it) # 2
next(it) # 3
next(it) # 5
next(it) # 8
next(it) # Exception

for e in FibIter(10):
    print(e)

# Il est possible de définir un itérateur infini => Appel à next manuel

# Exercice : Implémentation de la méthode reversed()
# => Renvoie un itérateur qui parcours la liste à l'envers
class Reversed:
    def __init__(self, list):
        self.list = list
        self.idx = len(list)
    def __next__(self):
        if self.idx > 0:
            self.idx -= 1
            return self.list[self.idx]
        else:
            raise StopIteration()
    def __iter__(self):
        return self
