from sys import argv
import numpy as np

if len(argv) != 3:
    print(f'Usage: python {argv[0]} <max size of string> <size of language>')
    exit(-1)

if int(argv[2]) > ((1 << (int(argv[1]) + 1)) - 1):
    print(f'A language with maximum string size {argv[1]} can have size at most {(1 << (int(argv[1]) + 1)) - 1}')
    exit(-1)

print('')
prevstrings = {''}
for _ in range(int(argv[2]) - 1):
    string = ''
    while string in prevstrings:
        lenstr = np.random.choice(int(argv[1]))
        string = ''
        for _ in range(lenstr):
            string += np.random.choice(['0', '1'])
    prevstrings.add(string)
    print(string)
