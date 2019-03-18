while True:
    try:
        s = input()
        for i in range(len(s)):
            print(" " * i, end = "")
            print(*s[:len(s) - i:], sep = " ")
        print()
    except EOFError:
        break
