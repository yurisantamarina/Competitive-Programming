l = [int(i) for i in input().split()]
n = l[0]
k = l[2]
b = [int(i) for i in input().split()]
gap = []
for i in range(1, n):
    gap.append(b[i] - b[i - 1])
gap.sort()
print(sum(gap[0:(n-k):1]) + k)
