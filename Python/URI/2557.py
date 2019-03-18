while True:
    try:
        s = input().split("+")
        a = [s[0]]
        [a.append(i) for i in s[1].split("=")]
        if a[0].isalpha():
            print(int(a[2]) - int(a[1]))
        elif a[1].isalpha():
            print(int(a[2]) - int(a[0]))
        else:
            print(int(a[0]) + int(a[1]))
    except EOFError:
        break
