n = int(input())
for X in range(n):
    lin = [int(i) for i in input().split()]
    l = lin[0]
    r = lin[1]
    ans = ""
    for i in range(l, r + 1):
        ans += str(i)
    print(ans[::-1])
