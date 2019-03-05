def fib1(n):
    res = []
    a, b = 0, 1
    while b < n:
        res.append(b)
        a, b = b, a+b
    return res

def fib2(n):
    if n < 2:
        return n
    else:
        return fib2(n-1) + fib2(n-2)

if __name__ == "__main__": # Le module a été chargé ou exécuté ?
    import sys
    v = int(sys.argv[1]) # Argument défini en ligne de commande
    print(fib1(v))
