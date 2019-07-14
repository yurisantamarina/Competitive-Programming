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

vector<int> g[210];
vector<int> v;
int tam[210];
int grau[210];
int cost[210];
map<string, int> mapa;
int dp[210][210];
int idx;
int get(string s){
	if(mapa.count(s)) return mapa[s];
	return mapa[s] = idx++;
}

void dfs(int u){
	v.pb(u);
	
	tam[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		dfs(g[u][i]);
		tam[u] += tam[g[u][i]];
	}
	
}

int solve(int pos, int falta){
	if(falta <= 0) return 0;
	if(pos == v.size()) return 1e9;
	if(dp[pos][falta]!=-1) return dp[pos][falta];
	
	int ans = 1e9;
	ans = min(solve(pos+1, falta), cost[v[pos]] + solve(pos+tam[v[pos]], falta - tam[v[pos]]));
	
	return dp[pos][falta] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int falta;
	int n;
	string op;
	while (cin >> op)
	{
		if(op=="#") break;
		stringstream ss;
		v.clear();
		ss << op;
		ss >> n;
		cin >> falta;
		mapa.clear();
		for (int i = 0; i < 210; i++)
		{
			g[i].clear();
		}
		
		int u, vv;
		string name;
		idx = 0;
		int c;
		memset(grau, 0, sizeof grau);
		memset(tam, 0, sizeof tam);
		for (int i = 0; i < n; i++)
		{
			cin >> name >> c;
			getline(cin, op);
			ss.clear();
			ss << op;
			
			u = get(name);
			cost[u] = c;
			while (ss >> op)
			{
				vv = get(op);
				g[u].pb(vv);
				grau[vv]++;
			}
			
		}
		for (int i = 0; i < n; i++)
		{
			if(grau[i]==0) dfs(i);
		}
		
		memset(dp, -1, sizeof dp);
		cout << solve(0, falta) << "\n";
		
	}
	
	return 0;
}
