n#include <bits/stdc++.h>

using namespace std;
int n, t;
double q, p, dp[2010][2010];

double exp(double base, int e){
	if(e == 0) return 1.0;
	double aux = exp(base, e/2);
	aux = aux*aux;
	if(e & 1) aux *= base;
	return aux;
}

int main(){
	cin >> n >> p >> t;
	
	q = 1 - p;
	
	for (int i = 0; i <= t; i++)
		dp[0][i] = exp(q, i);
	
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= t; j++)
		{
			if(i == n) dp[i][j] = dp[i-1][j-1] * p + dp[i][j-1];
			else dp[i][j] = dp[i-1][j-1] * p + dp[i][j-1] * q;
		}
	}
	
	double ans = 0.0;
	for (int i = 0; i <= n; i++)
	{
		ans += dp[i][t] * i;
	}
	cout << fixed << setprecision(10) << ans << "\n";
	
	return 0;
}
