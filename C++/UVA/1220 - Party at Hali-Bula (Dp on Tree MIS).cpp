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

int idx;
bool unico;
map<string, int> mapa;
vector<int> g[210];
int dp[210][2];


int get(string s){
	if(mapa.count(s)) return mapa[s];
	return mapa[s] = idx++;
}

int solve(int u, int pai, int pega){
	if(dp[u][pega]!=-1) return dp[u][pega];
	
	
	int ans = 0;
	if(pega){
		for (int i = 0; i < g[u].size(); i++)
		{
			if(g[u][i]==pai) continue;
			ans += solve(g[u][i], u, false);
		}
		ans++;
	}else{
		for (int i = 0; i < g[u].size(); i++)
		{
			if(g[u][i]==pai) continue;
			int a = solve(g[u][i], u, false);
			int b = solve(g[u][i], u, true);
			ans += max(a, b);
		}
		
	}
	
	
	return dp[u][pega] = ans;
}

void path(int u, int pai, int pega){
	if(!unico) return;
	
	int ans = 0;
	if(pega){
		for (int i = 0; i < g[u].size(); i++)
		{
			if(g[u][i]==pai) continue;
			path(g[u][i], u, false);
		}
	}else{
		for (int i = 0; i < g[u].size(); i++)
		{
			if(g[u][i]==pai) continue;
			int a = solve(g[u][i], u, false);
			int b = solve(g[u][i], u, true);
			if(a==b){
				unico = false;
				return;
			}
			if(a>b){
				path(g[u][i], u, false);
			}else{
				path(g[u][i], u, true);
			}
		}
		
	}
	
	
}
int n;
void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
	mapa.clear();
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	while (cin >> n, n)
	{
		string bigBoss;
		cin >> bigBoss;
		
		mapa.clear();
		reset();
		
		mapa[bigBoss] = 0;
		idx = 1;
		string s1, s2;
		int u, v;
		for (int i = 0; i < n-1; i++)
		{
			cin >> s1 >> s2;
			u = get(s1);
			v = get(s2);
			g[u].pb(v);
			g[v].pb(u);
		}
		unico = true;
		memset(dp, -1, sizeof dp);
		int ansA = solve(0, 0, false);
		int ansB = solve(0, 0, true);
		if(ansA == ansB){
			unico = false;
		}else if(ansA > ansB){
			path(0, 0, false);
		}else{
			path(0, 0, true);
		}
		
		cout << max(ansA, ansB) << " " << (unico ? "Yes" : "No") << "\n"; 
	}
	
		
	return 0;
}
