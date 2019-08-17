def solve(i, sz):
    if i == len(s):
        return sz == k
    if dp[i][sz] != -1:
        return dp[i][sz]
    
    ans = False
    if s[i].isalpha():
        ans = solve(i + 1, sz + 1)
    else:
        ans = solve(i + 1, sz) or solve(i + 1, sz - 1)
        if s[i] == '*':
            for j in range(i, 402):
                if sz + j - 1 > 500:
                    break
                ans = ans or solve(i + 1, sz + j - 1)

    dp[i][sz] = ans
    return ans

def path(i, sz):
    if i == len(s):
        return

    ans = solve(i, sz)
    if s[i].isalpha():
        resp.append(s[i])
        path(i + 1, sz + 1)
    else:
        if ans == solve(i + 1, sz):
            path(i + 1, sz)
        elif ans == solve(i + 1, sz - 1):
            resp.pop()
            path(i + 1, sz - 1)
        elif s[i] == '*':
            for j in range(i, 402):
                if sz + j - 1 > 500:
                    break
                if ans == solve(i + 1, sz + j - 1):
                    path(i + 1, sz + j - 1)
                    return

                resp.append(s[i - 1])

s = input()
k = int(input())

dp = [0] * len(s)
for i in range(len(s)):
    dp[i] = [-1] * 710

ans = solve(0, 0)
resp = []

if ans:
    path(0, 0)
    print(*resp, sep = "")
else:
    print("Impossible")
