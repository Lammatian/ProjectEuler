from heapq import heappush, heappop

def neighbours(x, y, W, H):
    ns = []
    if y + 1 < H:
        ns.append((x, y+1))
    if y - 1 >= 0:
        ns.append((x, y-1))
    if x + 1 < W:
        ns.append((x+1, y))

    return ns

def one_best_path(matrix, start, end):
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

def best_path(matrix):
    best_cost = 1e9
    
    for start_y in range(len(matrix)):
        for end_y in range(len(matrix)):
            start = (0, start_y)
            end = (len(matrix[0]) - 1, end_y)
            best_cost = min(best_cost, one_best_path(matrix, start, end))

    return best_cost

def main():
    with open('p082_matrix.txt') as f:
        matrix = list(map(lambda x: list(map(int, x.split(','))), f.readlines()))
    
    print(matrix)
    print(one_best_path(matrix, (0,0), (79, 79)))
    print(best_path(matrix))

if __name__ == '__main__':
    main()
