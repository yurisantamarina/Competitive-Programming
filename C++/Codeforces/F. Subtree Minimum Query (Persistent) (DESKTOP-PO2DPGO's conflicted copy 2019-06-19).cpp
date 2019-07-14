#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define MAXN 101010

struct node{
	int val, l, r;
};

node st[10101010];
vector<int> euler;
vector<int> g[MAXN];
int peso[MAXN];
int root[MAXN];
int pos[MAXN];
int H[MAXN];
int sz[MAXN];
vector<int> vet[MAXN];
int nxt = 1;

void dfs(int u, int pai, int h){
	euler.pb(u);
	pos[u] = (int)euler.size()-1;
	H[u] = h;
	sz[u] = 1;
	
	vet[h].pb(u);
	for(int v : g[u]){
		if(v == pai) continue;
		dfs(v, u, h+1);
		sz[u] += sz[v];
	}
}

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	
	int clone = nxt++;
	st[clone] = st[no];
	
	if(l==r){
		st[clone].val = min(st[clone].val, val);
		return clone;
	}
	int mid = (l+r)/2;
	
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].val = min(st[st[clone].l].val, st[st[clone].r].val);
	
	return clone;
}

int query(int no, int l, int r, int i, int j){
	if(r < i || l > j) return 1e9;
	if(i <= l && r <= j){
		return st[no].val;
	}
	int mid = (l+r)/2;
	
	return min(query(st[no].l, l, mid, i, j), query(st[no].r, mid+1, r, i, j));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, raiz, u, v, q, l, r;
	cin >> n >> raiz;
	for (int i = 1; i <= n; i++)
	{
		cin >> peso[i];
	}
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	for (int i = 0; i < 10101010; i++)
	{
		st[i].val = 1e9;
	}
	
	
	euler.pb(0);
	dfs(raiz, raiz, 1);
	
	root[0] = 0;
	for (int h = 1; h <= n; h++)
	{
		root[h] = root[h-1];
		for (int i = 0; i < (int)vet[h].size(); i++)
		{
			root[h] = update(root[h], 1, n, pos[vet[h][i]], peso[vet[h][i]]);
		}
	}
	cin >> q;
	int lst = 0;
	int x, k, P, Q, mx;
	for (int i = 0; i < q; i++)
	{
		cin >> P >> Q;
		x = ((P + lst) % n) + 1;
		k = ((Q + lst) % n);
		
		mx = min(n, H[x] + k);
		
		cout << (lst = query(root[mx], 1, n, pos[x], pos[x]+sz[x]-1)) << "\n";
	}
	
	
	
	return 0;
}
