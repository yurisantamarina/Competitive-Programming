MOD = 10**9 + 7

def get(x, resto):
    return x // 3 + (1 if x % 3 >= resto else 0)

lin = [int(i) for i in input().split()]
n = lin[0]
l = lin[1]
r = lin[2]

resto0 = get(r, 0) - get(l - 1, 0)
resto1 = get(r, 1) - get(l - 1, 1)
resto2 = get(r, 2) - get(l - 1, 2)

zero = resto0
um = resto1
dois = resto2

for i in range(1, n):
    a = (zero * resto0 + um * resto2 + dois * resto1) % MOD
    b = (zero * resto1 + um * resto0 + dois * resto2) % MOD
    c = (zero * resto2 + um * resto1 + dois * resto0) % MOD
    zero = a
    um = b
    dois = c

print(zero)
