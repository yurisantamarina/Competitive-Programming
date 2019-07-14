n = int(input())
vetor = [int(i) for i in input().split()]
menor = min(vetor)
posicao = 0
for i in range(len(vetor)):
    if vetor[i] == menor:
        posicao = i
        break

print("Menor valor: " + str(menor))
print("Posicao: " + str(posicao))
