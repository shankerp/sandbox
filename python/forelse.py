#!/usr/bin/python

print ''
for n in range(2,10):
    for x in range(2,n):
        if n % x == 0:
            print n, 'equals', x, '*', n/x
            break
    else:
        print n, 'is a prime number'

print ''
print 'Prime numbers in the range 2 to 100'
for n in range(2, 100):
    for x in range(2, n):
        if n % x == 0:
            #print n, 'equals', x, '*', n/x
            break
    else:
        #print n, 'is a prime number'
        print n, 
print ''
print ''
