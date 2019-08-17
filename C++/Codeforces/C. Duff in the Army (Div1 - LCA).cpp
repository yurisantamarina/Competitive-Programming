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
#define MAXN 100010

vector<int> pessoas[MAXN][20];

vector<int> g[MAXN];
int h[MAXN];
vector<int> vive[MAXN];
int lca[MAXN][20];

vector<int> merge(vector<int> &a, vector<int> &b){
	vector<int> ans;
	int i = 0;
	int j = 0;
	
	while (1)
	{
		if((i==a.size() && j==b.size()) || ans.size() == 10) break;
		if(i==a.size()){
			ans.pb(b[j++]);
		}else if(j==b.size()){
			ans.pb(a[i++]);
		}else{
			if(a[i] == b[j]){
				ans.pb(a[i++]);
				j++;
			}else if(a[i] > b[j]){
				ans.pb(b[j++]);
			}else{
				ans.pb(a[i++]);
			}
		}
	}
	
	return ans;
}

void dfs(int u, int pai){
	if(u!=pai) h[u] = h[pai] + 1;
	lca[u][0] = pai;
	pessoas[u][0] = merge(vive[u], vive[pai]);
	
	for (int i = 1; i < 20; i++)
	{
		lca[u][i] = lca[lca[u][i-1]][i-1];
		pessoas[u][i] = merge(pessoas[u][i-1], pessoas[lca[u][i-1]][i-1]);
	}
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i]==pai) continue;
		dfs(g[u][i], u);
	}
}



vector<int> solve(int u, int v){
	if(h[u] < h[v]){
		swap(u, v);
	}
	vector<int> ans = merge(vive[u], vive[v]);
	int d = abs(h[u] - h[v]);
	for (int i = 19; i >= 0; i--)
	{
		if(d & (1<<i)){
			ans = merge(ans, pessoas[u][i]);
			u = lca[u][i];
		}
	}
	if(u==v){
		return ans;
	}
	
	for (int i = 19; i >= 0; i--)
	{
		if(lca[u][i] != lca[v][i]){
			ans = merge(ans, pessoas[u][i]);
			ans = merge(ans, pessoas[v][i]);
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	
	return merge(ans, vive[lca[u][0]]);
}

void printa(){
	for (int i = 0; i < 5; i++)
	{
		cout << "vértice " << i+1 << endl;
		for (int j = 0; j < 3; j++)
		{
			for(int k=0; k<pessoas[i][j].size(); k++){
				cout << pessoas[i][j][k] << ", ";
			}
			cout << "  ";
		}
		cout << endl << endl;
	}
	
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int u, v, n, m, q, x, a;
	cin >> n >> m >> q;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	for (int i = 0; i < m; i++)
	{
		cin >> x;
		x--;
		vive[x].pb(i+1);
	}
	
	h[0] = 0;
	dfs(0, 0);
	
	//~ printa();
	vector<int> ids;
	int k;
	for (int i = 0; i < q; i++)
	{
		cin >> u >> v >> a;
		u--; v--;
		ids = solve(u, v);
		k = min((int)ids.size(), a);
		cout << k << " ";
		for(int j = 0; j < k; j++){
			cout << ids[j] << " ";
		}
		cout << "\n";
	}
	
	
	
	
	
	
	
	return 0;
}
