# TD2
d = {}
def f(a, b, _cache = {}):
    if (a, b) in _cache:
        print("Dans le dico !")
        return _cache[(a, b)]
    else:
        print("Pas dans le dico ...")
        res = a ** b
        _cache[(a, b)] = res
        return res

r = f(5,2)
print(r)
r = f(5,2)
