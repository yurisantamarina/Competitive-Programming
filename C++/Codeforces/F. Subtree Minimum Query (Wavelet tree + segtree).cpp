#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
#define INF 1e9 + 10

struct ST{
	vector<int> st, v;
	int n;
	ST(){}
	ST(vector<int> &_v){
		v = _v;
		n = (int)v.size();
		st.resize(4 * n);
		build(1, 1, n);
	}
	void build(int no, int l, int r){
		if(l > r) return;
		if(l == r){
			st[no] = v[l-1];
			return;
		}
		int nxt = 2 * no, mid = (l + r) / 2;
		build(nxt, l, mid);
		build(nxt+1, mid+1, r);
		st[no] = min(st[nxt], st[nxt+1]);
	}
	int query(int no, int l, int r, int i, int j){
		if(r < i || l > j) return INF;
		if(i <= l && r <= j) return st[no];
		int nxt = 2 * no, mid = (l + r) / 2;
		return min(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
	}
};


int h[MAXN], ini[MAXN], sz[MAXN], a[MAXN], vet[MAXN];
vector<int> g[MAXN], euler;


struct wavelet{
	int lo, hi;
	vector<int> b, val;
	ST st;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn;
		hi = mx;
		
		//builda segtree
		if(from == to) return;
		val.clear();
		for(int *i = from; i != to; i++)
			val.pb(a[*i]);
		st = ST(val);
		if(mn == mx) return;
		
		int mid = (lo+hi)/2;
		auto f = [mid](int i){
			return h[i] <= mid;
		};
		
		b.pb(0);
		for(int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int query(int l, int r, int k){
		if(l > r) return INF;
		if(hi <= k) return st.query(1, 1, st.n, l, r);
		if(lo > k) return INF;
		return min(left->query(b[l-1] + 1, b[r], k), right->query((l-1) - b[l-1] + 1, r - b[r], k));
	}
};

int dfs(int u, int pai, int alt){
	h[u] = alt;
	ini[u] = (int)euler.size();
	euler.pb(u);
	sz[u] = 1;
	
	for(int v : g[u])
		if(v != pai)
			sz[u] += dfs(v, u, alt + 1);
	
	return sz[u];
}


int main(){
	int n, raiz, u, v;
	
	scanf("%d %d", &n, &raiz);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < n-1; i++)
	{
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(raiz, raiz, 0);
	for (int i = 0; i < (int)euler.size(); i++)
		vet[i+1] = euler[i];
	
	wavelet *root = new wavelet(vet + 1, vet + n + 1, 0, n+1);
	int lst = 0, q, pi, qi, k;
	
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d %d", &pi, &qi);
		u = ((pi + lst) % n) + 1;
		k = ((qi + lst) % n);
		printf("%d\n", lst = root->query(ini[u] + 1, ini[u] + sz[u], h[u] + k));
	}
	
	return 0;
}
