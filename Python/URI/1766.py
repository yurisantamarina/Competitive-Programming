def cmp(a):
	return (-a[1], a[2], a[3], a[0])

t = int(input())

#leitura das renas  : nome, peso, idade, altura
#ordenacao das renas: D peso, C idade, C altura, C nome

for TC in range(t):
	n, m = [int(i) for i in input().split()]

	renas = []
	for i in range(n):
		lin = input().split();
		renas.append([str(lin[0]), int(lin[1]), int(lin[2]), float(lin[3])]);

	renas.sort(key = cmp)

	print("CENARIO {%d}" % (TC + 1))
	print(*["{} - {}".format(i + 1, renas[i][0]) for i in range(m)], sep = "\n")