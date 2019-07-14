//~ http://codeforces.com/group/kZPk3ZTzR5/contest/101418/problem/E

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
int n;
int meio = 5010;
int v[110];
int dp[2][5010*2];

int solve(){
	
	for (int pos = n; pos >= 0; pos--)
	{
		for (int gap = 0; gap < 2*meio; gap++)
		{
			dp[pos & 1][gap] = 1e9;
			if(pos==n){
				dp[pos & 1][gap] = abs(meio - gap);
			}else{
				if(gap + v[pos] < 2*meio) dp[pos & 1][gap] = min(dp[pos & 1][gap], dp[(pos+1) & 1][gap+v[pos]]);
				if(gap - v[pos] >= 0) dp[pos & 1][gap] = min(dp[pos & 1][gap], dp[(pos+1) & 1][gap-v[pos]]);
			}
		}
	}
	return dp[0 & 1][meio];
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	while (cin >> n, n)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		cout << solve() << "\n";
	}
	
		
	return 0;
}
