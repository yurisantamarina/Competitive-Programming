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

int dp[1010][2];
vector<int> g[1010];
int n;

int solve(int u, int pai, bool pega){
	if(dp[u][pega]!=-1) return dp[u][pega];
	//~ printf("%d %s\n", u+1, pega ? "pega" : "nao pega");
	int ans = 0;
	if(pega){
		ans = 1;
		for (int i = 0; i < g[u].size(); i++)
		{
			if(g[u][i]==pai) continue;
			ans += min(solve(g[u][i], u, true), solve(g[u][i], u, false));
		}
	}else{
		ans = 0;
		for (int i = 0; i < g[u].size(); i++)
		{
			if(g[u][i]==pai) continue;
			ans += solve(g[u][i], u, true);
		}
		
	}
	
	return dp[u][pega] = ans;
}

void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
	
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int q;
	while (cin >> n, n)
	{
		reset();
		int u;
		for (int i = 0; i < n; i++)
		{
			cin >> q;
			while (q--)
			{
				cin >> u;
				g[i].pb(u-1);
			}
			
		}
		memset(dp, -1, sizeof dp);
		//~ oioi;
		if(n==1) cout << 1 << "\n";
		else cout << min(solve(0, 0, true), solve(0, 0, false)) << "\n";
	}
	
	return 0;
}
