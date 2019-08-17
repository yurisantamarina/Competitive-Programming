#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define MAXN 101010
#define LOG 20
typedef long long int ll;

struct node{
	int sum, l, r;
};

int RAIZ = 1;
int nxt = 1;
int lca[MAXN][LOG];
vector<int> g[MAXN];
int val[MAXN];
int parent[MAXN];
int root[MAXN];
int h[MAXN];
int n, q;
node st[10101010];
map<int, int> mapa;
map<int, int> rev;

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	
	int clone = nxt++;
	st[clone] = st[no];
	
	if(l == r){
		st[clone].sum += val;
		return clone;
	}
	
	int mid = (l+r)/2;
	
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

void dfs(int u, int pai){
	parent[u] = pai;
	h[u] = h[pai]+1;
	
	root[u] = update(root[pai], 0, n-1, val[u], 1);
	
	lca[u][0] = pai == 0 ? 1 : pai;
	for (int i = 1; i < LOG; i++)
		lca[u][i] = lca[lca[u][i-1]][i-1];
	
	int v;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		dfs(v, u);
	}
}

int getLca(int u, int v){
	if(h[u] < h[v]) swap(u, v);
	int d = abs(h[u] - h[v]);
	
	for (int i = 0; i < LOG; i++)
		if(d & (1<<i)) u = lca[u][i];
	
	if(u == v) return u;
	
	for (int i = LOG-1; i >= 0; i--)
	{
		if(lca[u][i] != lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	
	return lca[u][0];
}

int query(int noU, int noV, int noLca, int noPai, int l, int r, int k){
	if(l == r) return l;
	int sumEsq = st[st[noU].l].sum + st[st[noV].l].sum - st[st[noLca].l].sum - st[st[noPai].l].sum;
	
	int mid = (l+r)/2;
	
	if(sumEsq < k) return query(st[noU].r, st[noV].r, st[noLca].r, st[noPai].r, mid+1, r, k - sumEsq);
	return query(st[noU].l, st[noV].l, st[noLca].l, st[noPai].l, l, mid, k);
}

void mapeia(){
	set<int> s;
	
	for (int i = 1; i <= n; i++)
		s.insert(val[i]);
		
	int idx = 0;
	for(set<int>::iterator i = s.begin(); i != s.end(); i++){
		mapa[*i] = idx;
		rev[idx] = *i;
		idx++;
	}
	for (int i = 1; i <= n; i++)
	{
		val[i] = mapa[val[i]];
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> val[i];
	}
	
	int u, v, k;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	mapeia();
	root[0] = 0;
	dfs(1, 0);
	
	int LCA;
	for (int i = 0; i < q; i++)
	{
		cin >> u >> v >> k;
		LCA = getLca(u, v);
		cout << rev[query(root[u], root[v], root[LCA], root[parent[LCA]], 0, n-1, k)] << "\n";
	}
	
	
	return 0;
}
