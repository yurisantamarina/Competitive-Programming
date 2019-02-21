tc = int(input())
for TC in range(tc):
    n = int(input())
    word = []
    idioms = []
    for i in range(n):
        word = input()
        idioms.append(word)
    print("ingles" if len(list(set(idioms))) > 1 else idioms[0])
