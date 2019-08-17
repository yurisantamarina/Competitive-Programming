def getMin(i):
    a = (pref[i - 1] if i - 1 >= 0 else 10**10)
    b = (suf[i + 1] if i + 1 < n else 10**10)
    return min(a, b)

n = int(input())
v = [int(i) for i in input().split()]

pref = [0] * n
suf = [0] * n
pref[0] = v[0]
suf[n - 1] = v[n - 1]
j = n - 2
for i in range(1, n):
    pref[i] = min(pref[i - 1], v[i])
    suf[j] = min(suf[j + 1], v[j])
    j -= 1

tot = sum(v)
ans = tot
for i in range(n):
    div = 1
    while div * div <= v[i]:
        if v[i] % div == 0:
            mn = getMin(i)
            ans = min(ans, tot - v[i] - mn + (v[i] / div) + mn * div)
        div += 1
print(int(ans))
