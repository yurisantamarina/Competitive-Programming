entrada = [int(i) for i in input().split()]

h1 = entrada[0]
m1 = entrada[1]
h2 = entrada[2]
m2 = entrada[3]

total1 = h1 * 60 + m1
total2 = h2 * 60 + m2

if total1 < total2:
    duration = total2 - total1
else:
    duration = (24 * 60 - total1) + total2

hours = int(duration / 60)
minutes = duration % 60
print("O JOGO DUROU " + str(hours) + " HORA(S) E " + str(minutes) + " MINUTO(S)")
