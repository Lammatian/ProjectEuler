from math import log

#N = 10**8
N = 10**9
#primes = [2, 3, 5]
primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

def rec(curr, largest_prime, bound):
    if curr > bound:
        return 0

    result = 1 + sum(rec(curr * p, p, bound) for p in primes if p >= largest_prime)
    return result
            
print(rec(1, 1, N))
