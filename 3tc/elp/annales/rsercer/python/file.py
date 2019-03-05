

def find_max_len(*args):
    if not args:
        return 0
    return max([len(a) for a in args])

def Enumerate(array):
    it = iter(array)
    while True:
        yield next(it)
