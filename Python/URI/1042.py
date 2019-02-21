entrada = input().split()

valores = [int(i) for i in entrada]
##aux = list(valores) - copiar um lista sem ser por referência
valores.sort()

print(*valores, sep = '\n')
print()
print(*entrada, sep = '\n')
