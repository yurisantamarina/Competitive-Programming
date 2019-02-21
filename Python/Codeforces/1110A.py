l = [int(i) for i in input().split()]
b = l[0]
k = l[1]
a = [int(i) for i in input().split()]

at = 0
for i in a:
    at *= b
    at += i
    at %= 2

print("even" if at == 0 else "odd")
