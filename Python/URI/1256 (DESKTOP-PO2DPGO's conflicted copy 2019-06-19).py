tc = int(input())

for K in range(tc):
    l = [int(i) for i in input().split()]
    mod = l[0]
    n = l[1]
    mapa = {}
    v = [int(i) for i in input().split()]
    for i in v:
        if i % mod in mapa:
            mapa[i % mod].append(i)
        else:
            mapa[i % mod] = [i]

    for i in range(mod):
        if i not in mapa:
            print("{} -> \\".format(i))
        else:
            print("{} -> ".format(i), end = "")
            print(*mapa[i], sep = " -> ", end = " -> \\\n")

    if K < tc - 1:
        print()
