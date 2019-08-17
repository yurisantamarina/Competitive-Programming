while True:
    try:
        s = input()
        for c in s:
            if c.isalpha():
                if c.islower():
                    print(chr((ord(c) - ord('a') + 13) % 26 + ord('a')), end="")
                else:
                    print(chr((ord(c) - ord('A') + 13) % 26 + ord('A')), end="")
            else:
                print(c, end="")
        print()
    except EOFError:
         break



