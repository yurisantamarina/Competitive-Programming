#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN 101010
#define LOG 20

struct node{
	int l, r, sum;
	node(){}
	node(int a, int b, int c){
		l = a;
		r = b;
		sum = c;
	}
};

node st[10101010];
vector<int> g[MAXN], lives[MAXN];
int lca[MAXN][LOG], h[MAXN], root[MAXN], parent[MAXN];
int cnt = 1;
int n, m, q;

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	int clone = cnt++;
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

int query(int noU, int noV, int noLCA, int noPai, int l, int r, int k){
	if(l == r){
		//~ printf("cheguei em %d com k = %d\n", l, k);
		return l;
	}
	//~ printf("l = %d  r = %d  k = %d\n", l, r, k);
	int sumEsq = st[st[noU].l].sum + st[st[noV].l].sum - st[st[noLCA].l].sum - st[st[noPai].l].sum;
	
	int mid = (l+r)/2;
	if(sumEsq >= k) return query(st[noU].l, st[noV].l, st[noLCA].l, st[noPai].l, l, mid, k);
	return query(st[noU].r, st[noV].r, st[noLCA].r, st[noPai].r, mid+1, r, k - sumEsq);
}

void dfs(int u, int pai){
	if(u == 1) lca[u][0] = u;
	else lca[u][0] = pai;
	
	h[u] = h[pai] + 1;
	
	for (int i = 1; i < LOG; i++)
		lca[u][i] = lca[lca[u][i-1]][i-1];
	
	parent[u] = pai;
	root[u] = root[pai];
	for (int i = 0; i < (int)lives[u].size(); i++){
		root[u] = update(root[u], 1, MAXN-1, lives[u][i], 1);
	}
	
	for(int v : g[u]){
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

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int u, v, x;
	cin >> n >> m >> q;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	for (int i = 1; i <= m; i++)
	{
		cin >> x;
		lives[x].pb(i);
	}
	
	root[0] = 0;
	h[0] = 0;
	dfs(1, 0);
	int ans, lc, a, sum;
	vector<int> saida;
	while (q--)
	{
		cin >> u >> v >> a;
		lc = getLca(u, v);
		x = parent[lc];
		//~ printf("lca %d %d = %d  parent[%d] = %d\n", u, v, lc, lc, x);
		saida.clear();
		
		sum = st[root[u]].sum + st[root[v]].sum - st[root[lc]].sum - st[root[x]].sum;
		a = min(a, sum);
		for (int i = 1; i <= a; i++)
		{
			ans = query(root[u], root[v], root[lc], root[x], 1, MAXN-1, i);
			if(ans == -1) break;
			saida.pb(ans);
		}
		cout << saida.size() << " ";
		for (int i = 0; i < saida.size(); i++)
			cout << saida[i] << " ";
		cout << "\n";
	}
	
	
	return 0;
}
