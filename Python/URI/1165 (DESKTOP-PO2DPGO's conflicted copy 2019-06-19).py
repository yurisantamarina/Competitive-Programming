import math

n = int(input())

while n > 0:
    n -= 1
    x = int(input())
    lim = int(math.sqrt(x)) + 2
    prime = True
    for i in range(2, x):
        if(i * i > x):
            break
        if x % i == 0:
            prime = False
            break
    if prime:
        print(str(x) + " eh primo")
    else:
        print(str(x) + " nao eh primo")
        
