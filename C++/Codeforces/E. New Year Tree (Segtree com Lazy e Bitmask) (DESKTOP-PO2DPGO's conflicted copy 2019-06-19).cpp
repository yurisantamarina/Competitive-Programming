#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
#define MAXN 400010

ll st[4*MAXN];
ll lazy[4*MAXN];
int cor[MAXN];
vector<int> gPlano;
int pos[MAXN];
int tamSub[MAXN];
vector<int> g[MAXN];
int n, q;

void dfs(int u, int ult){
	pos[u] = gPlano.size();
	gPlano.pb(u);
	tamSub[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if(v == ult) continue;
		dfs(v, u);
		tamSub[u] += tamSub[v];
	}
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = 1LL << cor[gPlano[l]];
		lazy[no] = 0;
		return;
	}
	
	int nxt = 2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no] = st[nxt] | st[nxt+1];
	lazy[no] = 0;
}

void update(int no, int l, int r, int i, int j, int color){
	int nxt = 2*no;
	
	if(lazy[no] != 0){
		st[no] = 1LL << lazy[no];
		if(l!=r){
			lazy[nxt] = lazy[no];
			lazy[nxt+1] = lazy[no];
		}
		lazy[no] = 0;
	}
	
	if(j<l || i>r) return;
	
	if(i<=l && r<=j){
		st[no] = 1LL << color;
		if(l!=r){
			lazy[nxt] = color;
			lazy[nxt+1] = color;
		}
		return;
	}
	
	int mid = (l+r)/2;
	update(nxt, l, mid, i, j, color);
	update(nxt+1, mid+1, r, i, j, color);
	
	st[no] = st[nxt] | st[nxt+1];
}

ll query(int no, int l, int r, int i, int j){
	int nxt = 2*no;
	if(lazy[no]!=0){
		st[no] = 1LL << lazy[no];
		if(l!=r){
			lazy[nxt] = lazy[no];
			lazy[nxt+1] = lazy[no];
		}
		lazy[no] = 0;
	}
	
	if(j<l || i>r) return 0LL;
	if(i<=l && r<=j) return st[no];
	
	int mid = (l+r)/2;
	return query(nxt, l, mid, i, j) | query(nxt+1, mid+1, r, i, j);
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n >> q;
	memset(st, 0, sizeof st);
	for (int i = 0; i < n; i++)
	{
		cin >> cor[i];
	}
	
	int u, v;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	dfs(0, 0);
	
	
	build(1, 0, n-1);
	
	int op, color;
	for (int i = 0; i < q; i++)
	{
		cin >> op;
		if(op==1){
			cin >> u >> color;
			u--;
			update(1, 0, n-1, pos[u], pos[u]+tamSub[u]-1, color);
		}else{
			cin >> u;
			u--;
			cout << __builtin_popcountll(query(1, 0, n-1, pos[u], pos[u]+tamSub[u]-1)) << "\n";
		}
	}
	
	
	
	
	
	
	return 0;
}
