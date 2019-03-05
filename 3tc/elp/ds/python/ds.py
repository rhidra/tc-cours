# Exercice 1.1
# functools.reduce permet de réduire le contenu d'un tableau à un seul de ses éléments

def my_reduce(f, it, init=None):
    it = iter(it)
    if init is None:
        try:
            init = next(it)
        except StopIteration:
            raise TypeError('Sequence initale vide !')
    accum_value = init
    for x in it:
        accum_value = f(accum_value, x)
    return accum_value

my_reduce(lambda x, y: x+y, [1,2,3,4,5], 10)
# -> 25

# Exercice 1.2
# zip crée un iterateur permettant de parcourir deux listes en même
# en générant un tuple composé d'un élément de chaque liste

class Zip:
    def __init__(self, *t):
        self.t = []
        for e in t:
            self.t.append(iter(e))
    def __iter__(self):
        return self
    def __next__(self):
        try:
            l = []
            for e in self.t:
                l.append(next(e))
            t = tuple(l)
            return t
        except StopIteration:
            raise StopIteration()

u = [1,2,3]
v = [4,5,6]
w = [7,8,9]

for t in Zip(u, v, w):
    print(t)

# Exercice 1.3
[my_reduce(lambda x, y : x+y, t)/3 for t in Zip(u,v,w)]
