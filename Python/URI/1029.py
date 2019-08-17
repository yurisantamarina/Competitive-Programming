def solve(self, n):
    if n == 0:
        return [0, 0]
    if n == 1:
        return [1, 0]
    if dp[n][0] != -1:
        return dp[n];
    
    l = solve(self, n - 2)
    r = solve(self, n - 1)

    dp[n] = [l[0] + r[0], l[1] + r[1] + 2]
    return dp[n]


dp = []
tc = int(input())

for i in range(50):
    dp.append([-1, -1])

while tc > 0:
    tc -= 1
    n = int(input())
    
    aux = solve(self, n)
    print("fib({}) = {} calls = {}".format(n, aux[1], aux[0]))
    
