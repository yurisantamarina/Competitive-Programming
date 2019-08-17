import math

class Pv:
    def __init__(self, ls, idx):
        self.x = ls[0]
        self.y = ls[1]
        self.id = idx
    def cima_baixo(self):
        return 0 if (self.y > 0 or (self.y == 0 and self.x > 0)) else 1
    def cross(self, other):
        return self.x * other.y - self.y * other.x
    def __lt__(self, other):
        if self.cima_baixo() != other.cima_baixo():
            return self.cima_baixo() < other.cima_baixo()
        return self.cross(other) > 0
    def printa(self):
        print("({}, {})".format(self.x, self.y))
    def norma(self):
        return math.sqrt(self.dot(self))
    def normasq(self):
        return self.dot(self)
    def dot(self, other):
        return self.x * other.x + self.y * other.y
    
    
n = int(input())
vec = []
for i in range(n):
    vec.append(Pv([int(i) for i in input().split()], i))

vec.sort()
resp = 100000
id1 = 0
id2 = 0
for i in range(n):
    u = vec[i]
    v = vec[i - 1]
    ang = math.acos(u.dot(v) / (u.norma() * v.norma()))
    if ang + 1e-10 < resp:
        resp = ang
        id1 = u.id
        id2 = v.id
        #u.printa()
        #v.printa()
    #print(math.degrees(ang))

print(id1 + 1, id2 + 1)
