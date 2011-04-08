#!/usr/bin/python

def fib(n):
    """Print a Fibonacci series up to n."""
    a,b = 0,1
    while a < n:
        print a,
        a, b = b, a+b

def fib2(n):
    """Return a list containing the Fibonacci series up to n."""
    result = []
    a, b = 0, 1
    while a < n:
        result.append(a)
        a, b = b, a+b
    return result

if __name__ == '__main__':
    fib(2000)
