//~ http://codeforces.com/contest/724/problem/E

#include <bits/stdc++.h>

using namespace std;
#define MAXN 10010
#define INF 10000000000000000LL
typedef long long int ll;
int n, c, p[MAXN], s[MAXN];
ll dp[2][2], a, b;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> c;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	
	ll ans = INF;
	for (int i = 1; i <= n; i++){
		for (int j = 0; j <= i; j++){
			a = j ? dp[(i-1)&1][(j-1)&1] + s[i] : INF;
			b = j > i-1 ? INF : dp[(i-1)&1][j&1] + p[i] + (ll)j * c;
			dp[i&1][j&1] = min(a, b);
			
			if(i == n) ans = min(ans, dp[i&1][j&1]);
		}
	}
	cout << ans << "\n";
	
	return 0;
}
