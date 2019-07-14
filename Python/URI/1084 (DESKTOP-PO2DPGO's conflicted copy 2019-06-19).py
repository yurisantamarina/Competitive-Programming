while True:
    try:
        linha = [int(i) for i in input().split()]
        n = linha[0]
        k = linha[1]
        cp = k
        if n == 0 and k == 0:
            break

        number = input()
        stack = []

        for i in number:
            while len(stack) > 0 and stack[-1] < i and k > 0:
                stack.pop()
                k -= 1
            stack.append(i)

        while k > 0:
            k -= 1
            stack.pop()

        print("".join(stack))

    except EOFError:
         break



