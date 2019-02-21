MOD = 1000000007
class mat:
    def __init__(self, m):
        self.n = len(m)
        self.v = [0] * self.n
        for i in range(self.n):
            self.v[i] = [0] * self.n
        for i in range(self.n):
            for j in range(self.n):
                self.v[i][j] = m[i][j]
        #self.v = list(m)
    def __mul__(self, other):
        ans = mat(self.v)
        for i in range(self.n):
            for j in range(self.n):
                ans.v[i][j] = 0
                for k in range(self.n):
                    ans.v[i][j] += self.v[i][k] * other.v[k][j]
                    ans.v[i][j] %= MOD
        return ans

def exp(e):
    #print("e = {}".format(e))
    if e == 0:
        return ident
    aux = exp(e // 2)
    aux *= aux
    if e % 2 != 0:
        aux *= base
    return aux

def fill(sz):
    global base, ident
    aux = [0] * sz
    for i in range(sz):
        aux[i] = [0] * sz
    base = mat(aux)
    ident = mat(aux)
    
    for i in range(sz):
        if i == 0:
            base.v[i][0] = 1
            base.v[i][sz - 1] = 1
        else:
            base.v[i][i-1] = 1
        ident.v[i][i] = 1
    #print(base.v, ident.v)

lin = input().split()
n = int(lin[0])
m = int(lin[1])

base = mat([])
ident = mat([])
if n < m:
    print(1)
else:
    fill(m)
    resp = exp(n - m + 1)
    print(sum(resp.v[0]) % MOD)
