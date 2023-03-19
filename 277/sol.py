from z3 import Int, simplify, solve, And, Solver
import z3
z3.set_option(max_args=10000000, max_lines=1000000, max_depth=10000000, max_visited=1000000)

seq = 'UDDDUdddDDUDDddDdDddDDUDDdUUDd'
#seq = 'DdDddUUdDD'
N = 10**15
#N = 10**6
x = Int('x')
s = x

ops = {
    'd': lambda x: (3 * x + 1) // 2,
    'D': lambda x: 3 * x,
    'U': lambda x: (3 * x - 2) // 4
}
which_op = {
    0: 'D',
    1: 'U',
    2: 'd'
}
next_num = {
    0: lambda x: x // 3,
    1: lambda x: (4 * x + 2) // 3,
    2: lambda x: (2 * x - 1) // 3
}

def prv(i, c):
    return ops[c](i)

def nxt_chr(i):
    return which_op[i % 3]

def nxt(i):
    return next_num[i % 3](i)

def sq(i):
    s = ''
    for _ in range(30):
        s += nxt_chr(i)
        i = next_num[i % 3](i)
    return s, i

for i in range(1, 10**9):
    x = i
    for op in seq[::-1]:
        last = x
        x = prv(x, op) 
        if last != nxt(x):
            break
    else:
        if x > N:
            print(i, x)
            print(sq(x))
            exit(1)
