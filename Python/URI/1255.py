n = int(input())
for N in range(n):
    text = input()
    mapa = {}
    mx = 0
    for i in text:
        if i.isalpha():
            c = i.lower()
            if c not in mapa:
                mapa[c] = 1
            else:
                mapa[c] += 1
            mx = max(mx, mapa[c])

    tmp = []
    for i, j in mapa.items():
        if j == mx:
            tmp.append(i)
    print(*sorted(list(set(tmp))), sep = "")
