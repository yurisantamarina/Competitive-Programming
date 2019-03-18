while True:
    try:
        n = int(input())
        if n == 0:
            break
        ans = n
        while n != 1:
            if n % 2 == 0:
                n //= 2
            else:
                n = 3 * n + 1
            ans = max(ans, n)
        print(ans)
    except EOFError:
        break
