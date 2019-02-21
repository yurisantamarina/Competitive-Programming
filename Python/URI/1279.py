def bissexto(n):
    return (n % 4 == 0 and n % 100 != 0) or (n % 400 == 0)

def hulu(n):
    return n % 15 == 0

def bulu(n):
    return n % 55 == 0 and bissexto(n)

fst = True
while True:
    try:
        n = int(input())
        if not fst:
            print()
        fst = False
        flag = False
        if bissexto(n):
            print("This is leap year.")
            flag = True
        if hulu(n):
            print("This is huluculu festival year.")
            flag = True
        if bulu(n):
            print("This is bulukulu festival year.")
            flag = True
        if not flag:
            print("This is an ordinary year.")
        
    except EOFError:
        break
