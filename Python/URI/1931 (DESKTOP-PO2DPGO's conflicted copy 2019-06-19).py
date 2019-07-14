import queue

INF = 10**10
def init():
    global g, dist
    dist = [0] * C
    for i in range(C):
        g[i] = []
        dist[i] = [INF, INF]
        
def add_edge(u, v, w):
    g[u].append([v, w])
    g[v].append([u, w])

def dijkstra(src):
    pq = queue.PriorityQueue()
    dist[src][0] = 0
    pq.put([dist[src][0], 0, src])
    while not pq.empty():
        top = pq.get()
        d = top[0]
        parity = top[1]
        u = top[2]
        if d > dist[u][parity]:
            continue

        for e in g[u]:
            v = e[0]
            w = e[1]
            if dist[u][parity] + w < dist[v][parity ^ 1]:
                dist[v][parity ^ 1] = dist[u][parity] + w
                pq.put([dist[v][parity ^ 1], parity ^ 1, v])
    
    return dist[C - 1][0] if dist[C - 1][0] < INF else -1

l = [int(i) for i in input().split()]
C = l[0]
V = l[1]
g = {}
dist = []
init()
for i in range(V):
    l = [int(i) for i in input().split()]
    u = l[0] - 1
    v = l[1] - 1
    w = l[2]
    add_edge(u, v, w)
print(dijkstra(0))
