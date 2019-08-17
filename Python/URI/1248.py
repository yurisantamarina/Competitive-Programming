n = int(input())

for j in range(n):
    dieta = set(input())
    cafe = set(input())
    almoco = set(input())

    if len((cafe.union(almoco)).difference(dieta)) > 0:
        print("CHEATER")
    else:
        print("".join(sorted(list(dieta.difference(cafe.union(almoco))))))
