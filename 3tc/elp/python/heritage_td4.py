# Héritage en Python

# Classe mère = classe base
# Classe fille = classe dérivée

class Shape:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y
    def __repr__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ")"
    def translate(self, dx, dy):
        self.x += dx
        self.y += dy
    def area(self): # Impossible de définir le comportement
        pass
    def perimeter(self):
        pass

s = Shape()

class Circle(Shape):
    def __init__(self, x = 0, y = 0, r = 0):
        #Shape.__init__(self, x, y) # Appel au constructeur de la classe base
        # super() renvoie une référence vers la classe base
        super().__init__(x, y)
        self.r = r
    # En définissant une méthode déjà définie dans la classe base
    # on redéfinit (écrase) la méthode
    def __repr__(self):
        return "(" + super().__repr__() + ":" + str(self.r) + ")"
    def area(self):
        return 3.14 * self.r ** 2
    def perimeter(self):
        return 2 * 3.14 * self.r

c = Circle()

# Vérifie qu'une classe est dérivée d'une autre classe
issubclass(Circle, Shape) # true
issubclass(Shape, Circle) # false

isinstance(s, Shape) # true
isinstance(c, Circle) # true
isinstance(s, Circle) # false
isinstance(c, Shape) # true

class Rectangle(Shape):
    def __init__(self, x = 0, y = 0, w = 0, h = 0):
        super().__init__(x, y)
        self.w = w
        self.h = h
    def __repr__(self):
        return "[" + super().__repr__() + ":" + str(self.w) + "x" + str(self.h) + "]"
    def area(self):
        return self.w * self.h
    def perimeter(self):
        return (self.w + self.h) * 2

class Square(Rectangle):
    def __init__(self, x = 0, y = 0, a = 0):
        super().__init__(x, y, a, a)


# Trie d'un tableau de formes en fonction de l'aire
import random
types = [Circle, Rectangle, Square]
shapes = []
for i in range(10):
    idx = random.randrange(0, 3)
    if types[idx] == Circle:
        shapes.append(Circle(r = random.randrange(0, 10)))
    elif types[idx] == Rectangle:
        shapes.append(Rectangle(w = random.randrange(0, 10), h = random.randrange(0, 10)))
    else:
        shapes.append(Square(a = random.randrange(0, 10)))
sorted(shapes, key=lambda s: s.area(), reverse=True)
