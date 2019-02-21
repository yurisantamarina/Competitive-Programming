n = int(input())
for G in range(n):
    words = [i[0] for i in input().split()]
    print(*words, sep = "")
