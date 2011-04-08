i = 5

def f(arg=i):
    print arg

def accumulate(a, L=[]):
    L.append(a)
    return L

def dontAccumulate(a, L=None):
    if L is None:
        L = []
    L.append(a)
    return L
