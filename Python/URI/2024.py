def get(i, j):
    if j == 0:
        return gift[i][0], gift[i][1]
    if j == 1:
        return gift[i][0], gift[i][2]
    if j == 2:
        return gift[i][1], gift[i][2]
    
def can(i, rot, lst):
    x_lst, y_lst = get(i - 1, lst)
    x, y = get(i, rot)
    if x_lst > y_lst:
        x_lst, y_lst = y_lst, x_lst
    if x > y:
        x, y = y, x
    return (True if x <= x_lst and y <= y_lst else False)

INF = 10**10
n = int(input())
gift = []
for i in range(n):
    gift.append([int(i) for i in input().split()])

dp = [0] * (n + 2)
for i in range(len(dp)):
    dp[i] = [-INF] * 5

dp[0][0] = gift[0][2]
dp[0][1] = gift[0][1]
dp[0][2] = gift[0][0]

for i in range(1, n):
    for rot in range(3):
        for lst in range(3):
            if can(i, rot, lst) == True:
                dp[i][rot] = max(dp[i][rot], dp[i - 1][lst] + gift[i][2 - rot])

print(max(max(dp[n - 1]), -1))
