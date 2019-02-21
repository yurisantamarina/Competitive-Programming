#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn; hi = mx;
		if(from == to || mn == mx) return;
		int mid = (lo+hi)/2;
		auto f = [mid](int i){
			return i <= mid;
		};
		
		b.pb(0);
		for (int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int kth(int l, int r, int k){
		if(lo == hi) return lo;
		int inLeft = b[r] - b[l-1];
		if(inLeft >= k) return left->kth(b[l-1] + 1, b[r], k);
		return right->kth((l-1) - b[l-1] + 1, r - b[r], k - inLeft);
	}
};

vector<int> euler, g[MAXN];
int ini[MAXN], sz[MAXN], n, val[MAXN], vet[MAXN], rev[MAXN], cp[MAXN];

int dfs(int u, int p){
	ini[u] = (int)euler.size();
	euler.pb(u);
	sz[u] = 1;
	for(int v : g[u])
		if(v != p)
			sz[u] += dfs(v, u);
	return sz[u];
}

void reset(){
	for (int i = 0; i <= n; i++)
		g[i].clear();
	euler.clear();
}

int main(){
	int tc, q, u, v, k;
	scanf("%d", &tc);
	while (tc--)
	{
		scanf("%d %d", &n, &q);
		
		reset();
		
		for (int i = 1; i <= n; i++){
			scanf("%d", &val[i]);
			cp[i] = val[i];
		}
		sort(cp + 1, cp + n + 1);
		for (int i = 1; i <= n; i++)
		{
			int m = lower_bound(cp + 1, cp + n + 1, val[i]) - cp;
			rev[m] = val[i];
			val[i] = m;
		}
		
		for (int i = 0; i < n-1; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		euler.pb(0);
		dfs(1, 1);
		for (int i = 1; i <= n; i++)
			vet[i] = val[euler[i]];
		
		wavelet *root = new wavelet(vet + 1, vet + n + 1, 1, n+2);
		
		while (q--)
		{
			scanf("%d %d", &u, &k);
			printf("%d ", rev[root->kth(ini[u], ini[u] + sz[u] - 1, k)]);
		}
		printf("\n");
	}
	
	
	
	return 0;
}
