def change(s):
    a = s.split("@")
    b = a[0].split("+")
    c = b[0].split(".")
    return "".join(c) + "@" + a[1]
    
n = int(input())
em = []
for i in range(n):
    em.append(change(input()))
print(len(list(set(em))))
