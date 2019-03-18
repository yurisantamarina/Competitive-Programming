lin = [int(i) for i in input().split()]
n = lin[0]
m = lin[1]
k = lin[2]
a = [int(i) for i in input().split()]

vet = []
for i in range(n):
    vet.append([a[i], i])
vet.sort(reverse = True)

sp = [False] * n
ans = 0
for i in range(k * m):
    sp[vet[i][1]] = True
    ans += vet[i][0]

ini = []
cnt = 0
for i in range(n):
    if sp[i] == True:
        cnt += 1
    if cnt == m:
        ini.append(i + 1)
        cnt = 0

print(ans)
print(*ini[0:k-1:1], sep = " ")
