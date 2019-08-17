from sys import stdin, stdout

def propagate(no, l, r):
    if lazy[no] == 0:
        return
    st[no] += (r - l + 1) * lazy[no]
    nxt = 2 * no
    if l != r:
        lazy[nxt] += lazy[no]
        lazy[nxt + 1] += lazy[no]
    lazy[no] = 0
    
def query(no, l, r, i, j):
    propagate(no, l, r)
    if j < l or r < i:
        return 0
    if i <= l and r <= j:
        return st[no]
    mid = (l + r) // 2
    nxt = 2 * no
    return query(nxt, l, mid, i, j) + query(nxt + 1, mid + 1, r, i, j)

def update(no, l, r, i, j, val):
    propagate(no, l, r)
    if j < l or r < i:
        return
    if i <= l and r <= j:
        lazy[no] += val
        propagate(no, l, r)
        return
    mid = (l + r) // 2
    nxt = 2 * no
    update(nxt, l, mid, i, j, val)
    update(nxt + 1, mid + 1, r, i, j, val)
    st[no] = st[nxt] + st[nxt + 1]

tc = int(input())

for TC in range(tc):
    lin = [int(x) for x in stdin.readline().split()]
    n = lin[0]
    q = lin[1]
    st = [0] * (4 * n)
    lazy = [0]* (4 * n)
    #print(st, lazy)

    for j in range(q):
        lin = [int(x) for x in stdin.readline().split()]
        if lin[0] == 1:
            stdout.write(str(query(1, 1, n, lin[1], lin[2])) + "\n")
        else:
            update(1, 1, n, lin[1], lin[2], lin[3])
