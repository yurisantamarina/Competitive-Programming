def maxBeauty():
	dp = [[0 for i in range(3)] for j in range(n)]
	dp[0][0] = max(a[0], 0)
	dp[0][1] = max(a[0] * x, 0)
	dp[0][2] = max(a[0], 0)

	ans = 0;
	ans = max([ans, dp[0][0], dp[0][1], dp[0][2]])
	for i in range(1, n):
		dp[i][0] = max(dp[i - 1][0] + a[i], 0)
		dp[i][1] = max(max(dp[i - 1][0], dp[i - 1][1]) + a[i] * x, 0)
		dp[i][2] = max(max(dp[i - 1][1], dp[i - 1][2]) + a[i], 0)
		ans = max([ans, dp[i][0], dp[i][1], dp[i][2]])

	return ans

lin = [int(i) for i in input().split()]
n = lin[0]
x = lin[1]

a = [int(i) for i in input().split()]

print(maxBeauty())
