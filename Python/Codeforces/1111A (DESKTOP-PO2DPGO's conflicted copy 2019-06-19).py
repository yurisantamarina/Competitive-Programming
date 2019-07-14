vowel = "aeiou"
s = input()
t = input()

if len(s) != len(t):
    print("No")
else:
    flag = True
    for i in range(len(s)):
        a = 0
        b = 0
        if s[i] in vowel:
            a = 1
        if t[i] in vowel:
            b = 1

        if a != b:
            flag = False
        if not flag:
            break

    if flag:
        print("Yes")
    else:
        print("No")
