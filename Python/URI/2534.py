while True:
  try:
    linha = input().split()
    n = int(linha[0])
    q = int(linha[1])

    vet = []
    for i in range(n):
        x = int(input())
        vet.append(x)

    vet.sort()
    vet.reverse()

    for i in range(q):
        x = int(input())
        print(vet[x - 1])

  except EOFError:
    break



