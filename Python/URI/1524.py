while True:
    try:
        l = [int(i) for i in input().split()]
        n = l[0]
        k = l[1]
        a = [int(i) for i in input().split()]
        gap = [a[0]]
        for i in range(1, n - 1):
            gap.append(a[i] - a[i - 1])
        gap.sort()
        ans = sum(gap[0:n-k:1])
        print(ans)
    except EOFError:
        break
