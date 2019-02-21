#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const ll dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const ll dy[] = {-1,0,0, 1,1, 1,-1,-1};
ll gcd (ll x, ll y) {return (y != 0 ? gcd (y, x%y) : x);}
ll lcm (ll x, ll y) {return (x / gcd (x, y) * y);}
#define MAXN 5050
#define MOD 100000

vector<int> g[MAXN];
vector<int> ts;
int n, m;
int num_path[MAXN];
int sum[MAXN];
char vis[MAXN];

void limpa(){
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
		num_path[i]=0;
		sum[i]=0;
		vis[i]=0;
	}
	ts.clear();
}

void dfs(int u){
	if(vis[u]) return;
	vis[u]=1;
	int ans=0;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		dfs(v);
	}
	ts.pb(u);

}

int main() {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int t, u, v;
	cin >> t;
	int caso=1;
	while (t--)
	{
		cin >> n >> m;
		limpa();
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v;
			g[u].pb(v);
		}
		dfs(1);
		reverse(ts.begin(), ts.end());
		num_path[1] = 1;
		sum[1] = 0;
		for (int i = 0; i < n; i++)
		{
			u = ts[i];
			for(int j=0; j < g[u].size(); j++){
				v = g[u][j];
				num_path[v] += num_path[u];
				sum[v] += (num_path[u] + sum[u]);
				num_path[v] %= MOD;
				sum[v] %= MOD;
			}
		}
		
		cout << "Case " << caso++ << ": " << sum[v] << " " << num_path[n] << "\n";
	}
	

    

    return 0;
}
