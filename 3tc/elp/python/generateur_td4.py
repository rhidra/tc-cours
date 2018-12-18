# Générateur

def FibGen(n):
    a, b = 0, 1
    while b < n:
        yield b
        a, b = b, a+b

# A chaque yield, l'état de la fonction est gelée
# Son fonctionnement reprend avec un appel à next()
# iter() et next() sont définis par défaut

f = FibGen(10)
it = iter(f)
next(it)
next(it)
next(it)


def reverse(seq):
    for i in range(len(seq)-1, -1, -1):
        yield seq[i]
for e in reverse(v)
    print(e)
