from random import randint
from collections import defaultdict

pos = 0
STEPS = 20000000
doubles = 0
D = 4
position_counts = defaultdict(int)
next_railway = {
    7: 15,
    22: 25,
    36: 5
}
next_utility = {
    7: 12,
    22: 28,
    36: 12 
}
chance = {
    1: lambda _: 0,
    2: lambda _: 10,
    3: lambda _: 11,
    4: lambda _: 24,
    5: lambda _: 39,
    6: lambda _: 5,
    7: lambda x: next_railway[x],
    8: lambda x: next_railway[x],
    9: lambda x: next_utility[x],
    10: lambda x: x - 3
}

for s in range(STEPS):
    d1 = randint(1, D)
    d2 = randint(1, D)
    if d1 == d2:
        doubles += 1
        if doubles == 3:
            pos = 10          
            doubles = 0
            position_counts[pos] += 1
            continue
    else:
        doubles = 0
    d = d1 + d2

    pos = (pos + d) % 40
    if pos in [2, 17, 33]:
        # Community chest
        card = randint(1, 16)
        if card == 1:
            # Go to start
            pos = 0
        elif card == 2:
            # Go to jail
            pos = 10
    elif pos in [7, 22, 36]:
        # Chance
        card = randint(1, 16)
        if card in chance:
            pos = chance[card](pos)
    elif pos == 30:
        pos = 10

    position_counts[pos] += 1

result = [(k, v / STEPS) for k, v in position_counts.items()]
print(sorted(result, key=lambda item: item[1], reverse=True))
