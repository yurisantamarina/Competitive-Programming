import queue

linha = [int(i) for i in input().split()]
n = linha[0]
m = linha[1]

v = [int(i) for i in input().split()]
c = [int(i) for i in input().split()]

pq = queue.PriorityQueue()
for i in range(n):
    pq.put([0, i])

for i in range(m):
    employee = pq.get()
    now = employee[0]
    idx = employee[1]
    pq.put([now + c[i] * v[idx], idx])

while pq.qsize() > 0:
    employee = pq.get()

print(employee[0])
