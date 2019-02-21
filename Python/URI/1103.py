while True:
  try:
    linha = [int(i) for i in input().split()]
    continua = False
    for i in linha:
        if i != 0:
            continua = True
            break
    if not continua:
        break

    h1 = linha[0]
    m1 = linha[1]
    h2 = linha[2]
    m2 = linha[3]

    tot1 = h1 * 60 + m1
    tot2 = h2 * 60 + m2

    if tot1 < tot2:
        ans = tot2 - tot1
    else:
        ans = (24 * 60) - tot1 + tot2

    print(ans)
    
  except EOFError:
    break
