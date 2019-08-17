s = list(filter(lambda x : x in "aeiou", input()))
print("S" if s == s[::-1] else "N")
