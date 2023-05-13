# Ashwin Abraham, 2023

'''
Currently, this checks only the atomic version of Szymanski's Protocol

TODO: Parse C/C++ programs as input
'''

def is_bad(config: str) -> bool:
    num = 0
    for x in config:
        if x == '9' or x == '10':
            num += 1
    return num <= 1

