import sys

print
print '#looping through dictionaries, key-value retrieved using iteritems()'
knights = {'gallahad': 'the pure', 'robin' : 'the brave'}
for k, v in knights.iteritems():
    print k, v
print

print '#looping through sequence, position index and corresponding value retrieved using enumerate()'
for i, v in enumerate(['tic', 'tac', 'toe']):
    print i, v
print

print '#loop over two or more sequences at the same time, pair with zip()'
questions = ['name', 'quest', 'favorite color']
answers = ['lance lot', 'the holy grail', 'blue']
for q, a in zip(questions, answers):
    print 'What is your {0}? It is {1}.'.format(q, a)
print

print '#loop over a sequence in reverse direction, call reversed() over the sequence'
for i in reversed(xrange(1,10)):
    print i,
sys.stdout.write("\n\n");

print '#loop over a sequence in sorted order, use sorted()'
basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
for f in sorted(set(basket)):
    print f
