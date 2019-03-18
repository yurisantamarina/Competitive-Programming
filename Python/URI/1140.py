while True:
    try:
        words = [i[0].lower() for i in input().split()]
        if(words[0][0] == "*"):
            break
        print("Y" if len(list(set(words))) == 1 else "N")
    except EOFError:
        break
