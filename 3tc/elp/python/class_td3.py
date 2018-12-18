# Les classes dans python

class MyClass:
    myPi = 3.17

# Une classe est de type type

# Instanciation
m = MyClass()
type(m) # __main__.MyClass

# Accès à la variable de la classe, partagée par toutes les instances
MyClass.myPi

# Constructeur
class MyClass:
    # Méthode constructeur
    def __init__(self, v):
        # Création d'un attribut à la volée
        self.value = v
    def f():
        print("Hello !")
    def set(self, v):
        self.value = v
    # __repr__ permet de créer une représentation textuelle de l'objet
    def __repr__(self):
        return "value = " + str(self.value)
    # Impossible d'écrire value, doit être self.value => Rien n'est implicite ici

m1 = MyClass(42)
m1.value # Affiche 42
# En python, tous les attributs sont publics
print(m1) # Appelle __repr__

m1.set(43)
m1.value # Affiche 43

# En réalité, toutes les méthodes qui ont un paramètre self fonctionnent comme ça
MyClass.set(m1, 43)
# Donc si la méthode opère sur l'objet, il est nécessaire de définir un self dans les paramètres de la méthode

m1.f() # Ne fonctionne pas car MyClass.f(m1) n'existe pas
# MyClass.f est l'équivalent d'une méthode static en Java

# Dans une classe, tout ce qui est codé avec __value est immédiatement remplacé par _MyClass__value

# Autre exemple
class Complex:
    def __init__(self, re = 0, im = 0):
        self.set(re, im)
    # A la place de __repr__ on peut utiliser __str__ mais c'est moins flexible
    def __repr__(self):
        return "(" + str(self.real) + "," + str(self.imag) + ")"
    def set(self, re = 0, im = 0):
        self.real = re
        self.imag = im
    def norm(self):
        import math
        return math.sqrt(self.real ** 2 + self.imag ** 2)
    # Méthode spéciale pour implémenter l'addition c1 + c2
    def __add__(self, c):
        pass
