from heapq import heappush, heappop

def neighbours(x, y, W, H):
    ns = []
    if y + 1 < H:
        ns.append((x, y+1))
    if y - 1 >= 0:
        ns.append((x, y-1))
    if x + 1 < W:
        ns.append((x+1, y))
    if x - 1 >= 0:
        ns.append((x-1, y))

    return ns

def best_path(matrix, start, end):
    visited = set([start])
    W = len(matrix[0])
    H = len(matrix)
    queue = [(matrix[start[1]][start[0]], start, [start])]

    while queue:
        cost, cur, path = heappop(queue)

        for n in neighbours(*cur, W, H):
            if n in visited:
                continue
            
            ncost = matrix[n[1]][n[0]]
            if n == end:
                return cost + ncost

            heappush(queue, (cost + ncost, n, path + [n]))
            visited.add(n)

def main():
    with open('p082_matrix.txt') as f:
        matrix = list(map(lambda x: list(map(int, x.split(','))), f.readlines()))
    
    print(matrix)
    print(best_path(matrix, (0,0), (79, 79)))

if __name__ == '__main__':
    main()
