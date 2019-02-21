def dfs(u):
    seen[u] = 1
    if not u in g:
        seen[u] = 2
        return False

    ans = False
    for v in g[u]:
        if seen[v] == 1:
            return True
        elif seen[v] == 0:
            ans = ans or dfs(v)
    seen[u] = 2;
    return ans

def add_edge(u, v):
    if u in g:
        g[u].append(v)
    else:
        g[u] = [v]

g = {}
seen = []

tc = int(input())
for C in range(tc):
    line = [int(i) for i in input().split()]
    n = line[0]
    m = line[1]

    g.clear()
    seen = [0] * (n + 2)
    
    for i in range(m):
        line = [int(i) for i in input().split()]
        u = line[0]
        v = line[1]
        u -= 1
        v -= 1
        
        add_edge(u, v)

    ans = False
    for u in range(n):
        if seen[u] == 0:
##            print("comecando dfs em {}".format(u))
            ans = ans or dfs(u)
        if(ans == True):
            break

    if ans == True:
        print("SIM")
    else:
        print("NAO")
