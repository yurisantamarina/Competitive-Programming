from collections import deque

while True:
    try:
        n = int(input())
        if n == 0:
            break
        disc = []
        q = deque()
        for i in range(1, n + 1):
            q.append(i)

        while True:
            if len(q) == 1:
                break
            disc.append(q.popleft())
            q.append(q.popleft())

        print("Discarded cards:", end = "")
        if n > 1:
            print(" ", end="")
        print(*disc, sep = ", ")
        print("Remaining card: {}".format(q.popleft()))

        del q
        del disc
    except EOFError:
         break



