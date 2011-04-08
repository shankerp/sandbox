def f(x):
    return x % 2 != 0 and x % 3 != 0

def cube(x):
    return x*x*x

def add(x, y):
    return x+y

print 'Numbers in range 2 to 25 divisible by 2 and 3 = ', filter(f, range(2, 25))
print 'Cubes of numbers between 1 and 11 = ', map(cube, range(1, 11))
seq = range(8)
print 'Sum of corresponding numbers from 1 to 8 = ', map(add, seq, seq)
print 'Sum of numbers between 1 to 11 = ', reduce(add, range(1,11))
