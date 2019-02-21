def fill():
    global dp
    dp = [0] * n
    for i in range(n):
        dp[i] = [0] * (k + 1)

while True:
    try:
        linha = [int(i) for i in input().split()]
        n = linha[0]
        k = linha[1]

        if n == 0 and k == 0:
            break

##        print("{} {}".format(n, k))
        v = [int(i) for i in input().split()]
        dp = []

##        print(*v, sep = ' ')
        fill()

##        print(dp)
        for i in range(n):
            dp[i][1] = 1

        for length in range(2, k + 1):
            for i in range(n):
                dp[i][length] = 0
                for j in range(i):
                    if v[j] < v[i]:
                        dp[i][length] += dp[j][length - 1]

        ans = 0
        for i in range(n):
            ans += dp[i][k]

        print(ans)
    except EOFError:
         break



