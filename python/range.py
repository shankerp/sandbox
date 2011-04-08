#!/usr/bin/python

print range(5,10)
print range(0,10,3)
print range(-10,-100,-30)

a = ['Mary', 'had', 'a', 'little', 'lamb']

for i in range(len(a)):
    print i, a[i]

for i in a[:]:
    print i
