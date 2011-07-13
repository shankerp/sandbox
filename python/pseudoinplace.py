import fileinput

processing_foo1s = False

for line in fileinput.input('1.txt', inplace=1):
  if line.startswith('foo1'):
    processing_foo1s = True
  else:
    if processing_foo1s:
      print 'foo bar'
    processing_foo1s = False
  print line,

