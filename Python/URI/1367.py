while True:
    try:
        n = int(input())
        if n == 0:
            break
        mapa = {}
        for i in list([chr(i) for i in range(ord('A'), ord('Z') + 1)]):
            mapa[i] = 0

        acc = 0
        pen = 0
        for j in range(n):
            lin = input().split()
            problem = lin[0]
            time = int(lin[1])
            verdict = lin[2]
            if verdict == "correct":
                acc += 1
                pen += mapa[problem] * 20 + time
            else:
                mapa[problem] += 1

        print(acc, pen)
            
    except EOFError:
        break
