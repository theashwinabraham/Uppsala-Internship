import copy
# Ashwin Abraham, 2023

'''
Currently, this checks only the atomic version of Szymanski's Protocol

TODO: Optimize the code and port to C++ (there is a lot of scope for optimization - this is a rough version)
TODO: Parse C/C++ programs as input
'''

def is_bad(config: str) -> bool:
    num = 0
    for x in config:
        if x == '9' or x == '10':
            num += 1
    return num <= 1

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
                    ret_set.add(config[:i] + '5' + config[i + 1 :])
            elif config[i] == '5':
                    for j in range(i + 1, len(config)):
                        if config[j] != '0' and config[j] != '1' and config[j] != '4' and config[j] != '5':
                            break
                    else:
                        ret_set.add(config[:i] + '0' + config[i + 1 :])
            else:
                assert(False)
    return ret_set

# TODO: Optimize all this by DP
def k_size_substrings(config: str, k: int, start: int) -> set:
    if k == 0 and start < len(config):
        return {''}
    retset = set()
    for i in range(start, len(config)):
        ks = k_size_substrings(config, k - 1, i + 1)
        for substr in ks:
            retset.add(config[k] + substr)
    return retset

def alpha(S: set, k: int) -> set:
    if k == 0 and S != set():
        return {''}
    retset = set()
    for config in S:
        for kk in range(k + 1):
            retset |= k_size_substrings(config, kk, 0)
    return retset

def integral(k: int, l: int, V: set) -> set:
    retset = {''} if '' in V else set()
    cset = {'0', '1', '2', '3', '4', '5'}
    ll = 1
    while True:
        for c in cset:
            if alpha({c}, k) <= V:
                retset.add(c)
        ll += 1
        if ll > l:
            break
        ncset = set()
        for c in ['0', '1', '2', '3', '4', '5']:
            for s in cset:
                ncset.add(c + s)
        cset = ncset
    return retset

def safe() -> bool:
    k = 0
    Bmin = {'55'}
    while k := k + 1:
        I = {'0'*k}
        R = post(I) | I
        while R != I:
            I = R
            R = post(R) | R
        ak = alpha(R, k)
        if ak & Bmin != set():
            return False
        nak = alpha(post(integral(k, k + 1, ak)), k)
        while nak != ak:
            ak = nak
            nak = alpha(post(integral(k, k + 1, nak)), k)
        if ak & Bmin == set():
            return True
