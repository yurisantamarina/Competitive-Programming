n = int(input())
v = [int(i) for i in input().split()]
mx = max(v)
cnt = 0
ans = 0
for i in v:
    if i == mx:
        cnt += 1
    else:
        cnt = 0
    ans = max(ans, cnt)
print(ans)
