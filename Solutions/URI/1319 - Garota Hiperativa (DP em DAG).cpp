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
const int MOD = 1e8;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

char tem[110][110];
char ini[110];
char fim[110];
vector<int> g[110];
pair<int, int> atv[110];
int n, m;
ll dp[110][110];

bool pode(int u, int pai, int v){
	if(pai==n) return true;
	if(tem[pai][v]) return false;
	return true;
}

bool inter(pair<int, int> a, pair<int, int> b){
	if(a.F == b.F) return false;
	return b.S > a.S && b.F <= a.S;
}

ll dfs(int u, int pai){
	if(fim[u]) return 1;
	if(dp[u][pai]!=-1) return dp[u][pai];
	
	
	ll ans = 0LL;
	for (int i = 0; i < g[u].size(); i++)
	{
		if(pode(u, pai, g[u][i])){
			ans += dfs(g[u][i], u);
			ans%=MOD;
		}
	}
	return dp[u][pai] = ans;
}

int main () {
	
	while (cin >> m >> n)
	{
		if(m==0 && n==0) break;
		for (int i = 0; i < n; i++)
		{
			ini[i] = 0;
			fim[i] = 0;
			g[i].clear();
			cin >> atv[i].F >> atv[i].S;
		}
		memset(tem, 0, sizeof tem);
		sort(atv, atv+n);
		for (int i = 0; i < n; i++)
		{
			if(atv[i].F==0) ini[i] = 1;
			if(atv[i].S==m) fim[i] = 1;
			for (int j = i+1; j < n; j++)
			{
				if(inter(atv[i], atv[j])){
					g[i].pb(j);
					tem[i][j] = 1;
					//~ cout << i << " -> " << j << endl;
				}
			}
		}
		ll ans = 0LL;
		memset(dp, -1, sizeof dp);
		for (int i = 0; i < n; i++)
		{
			if(ini[i]){
				//~ cout << i << " ";
				ans += dfs(i, n);
				ans %= MOD;
			}
			//~ if(fim[i]) cout << i << " ";
		}
		//~ cout << endl;
		cout << ans << "\n";
		
	}
	
		
	return 0;
}
