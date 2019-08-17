test_cases = int(input())

for K in range(test_cases):
    entrada = input().split()
    x = int(entrada[0])
    y = int(entrada[1])
    if x > y:
        x, y = y, x
    ans = 0
    for i in range(x + 1, y):
        if(i % 2 != 0):
            ans += i
    print(ans)
