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

I = {'0'} # I_1

def post(S: set) -> set:
    ret_set = set()
    for config in S:
        for i in range(len(config)):
            if config[i] == '0':
                ret_set.add(config[:i] + '1' + config[i + 1 :])
            elif config[i] == '1':
                for j in range(len(config)):
                    if config[j] != '0' and config[j] != '1' and config[j] != '2' and j != i:
                        break
                else:
                    ret_set.add(config[:i] + '3' + config[i + 1 : ])
            elif config[i] == '3':
                for j in range(len(config)):
                    if config[j] == '1' and j != i:
                        ret_set.add(config[:i] + '2' + config[i + 1 :])
                        break
                else:
                    ret_set.add(config[:i] + '4' + config[i + 1 :])
            elif config[i] == '2':
                for j in range(len(config)):
                    if config[j] == '4' and j != i:
                        ret_set.add(config[:i] + '4' + config[i + 1 :])
                        break
            elif config[i] == '4':
                for j in range(i):
                    if config[j] != '0' and config[j] != '1':
                        break
                else:
                    for j in range(i + 1, len(config)):
                        if config[j] != '0' and config[j] != '1' and config[j] != '4':
                            break
                    else:
                        ret_set.add(config[:i] + '0' + config[i + 1 :])
    return ret_set