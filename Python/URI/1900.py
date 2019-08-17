def calc(n):
    return n * (n - 1) / 2

n = int(input())
v = [int(i) for i in input().split()]
v.insert(0, 0)

acc = [0]
mapa = {}
mapa[0] = 1
for i in range(1, n + 1):
    acc.append(acc[-1] + v[i])
    if acc[-1] in mapa:
        mapa[acc[-1]] += 1
    else:
        mapa[acc[-1]] = 1
ans = 0
for i in mapa.values():
    ans += calc(i)

print(int(ans))
