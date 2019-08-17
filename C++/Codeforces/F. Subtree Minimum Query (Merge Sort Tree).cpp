#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 100000000000000LL
typedef long long int ll;

vector<ll> g[MAXN];

struct node{
	vector<ll> alt;
	vector<ll> mnAcc;
	node(){
		alt.clear();
		mnAcc.clear();
	}
};

node st[MAXN*4];
ll h[MAXN];
ll ini[MAXN];
ll fim[MAXN];
ll cost[MAXN];
vector<ll> euler;

void dfs(int u, int pai){
	ini[u] = (int)euler.size();
	euler.pb(u);
	
	h[u] = h[pai] + 1;
	for(int v : g[u]){
		if(v == pai) continue;
		dfs(v, u);
	}
	
	fim[u] = (int)euler.size() - 1;
}

void merge(int no, int esq, int dir){
	st[no] = node();
	int i = 0, j = 0;
	int szEsq = (int)st[esq].alt.size();
	int szDir = (int)st[dir].alt.size();
	
	while (i < szEsq && j < szDir)
	{
		if(h[st[esq].alt[i]] < h[st[dir].alt[j]]){
			st[no].alt.pb(st[esq].alt[i++]);
		}else{
			st[no].alt.pb(st[dir].alt[j++]);
		}
	}
	while (i < szEsq)
	{
		st[no].alt.pb(st[esq].alt[i++]);
	}
	while (j < szDir)
	{
		st[no].alt.pb(st[dir].alt[j++]);
	}
	
	st[no].mnAcc.pb(cost[st[no].alt[0]]);
	for (int i = 1; i < (int)st[no].alt.size(); i++)
	{
		st[no].mnAcc.pb(min(st[no].mnAcc[i-1], cost[st[no].alt[i]]));
	}
	
	//~ if(no == 1){
		//~ cout << "oi\n";
		//~ for (int i = 0; i < (int)st[no].alt.size(); i++)
		//~ {
			//~ cout << h[st[no].alt[i]] << ' ';
		//~ }
		//~ cout << endl;
		//~ for (int i = 0; i < (int)st[no].alt.size(); i++)
		//~ {
			//~ cout << st[no].mnAcc[i] << ' ';
		//~ }
		//~ cout << endl;
		
	//~ }
}

ll x;
ll getAns(int no, ll k){
	ll hMax = h[x] + k;
	ll ans = -1;
	
	ll lo = 0, hi = st[no].alt.size()-1, mid;
	
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(h[st[no].alt[mid]] <= hMax){
			ans = max(ans, mid);
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	
	if(ans == -1) return INF;
	return st[no].mnAcc[ans];
}

ll query(int no, int l, int r, int i, int j, ll k){
	if(r < i || l > j) return INF;
	if(i<=l && r<=j) return getAns(no, k);
	
	int mid = (l+r)/2;
	int nxt = 2*no;
	
	return min(query(nxt, l, mid, i, j, k), query(nxt+1, mid+1, r, i, j, k));
}

void build(int no, int l, int r){
	if(l == r){
		st[no] = node();
		st[no].alt.pb(euler[l]);
		st[no].mnAcc.pb(cost[euler[l]]);
		return;
	}
	int mid = (l+r) / 2;
	int nxt = 2*no;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	merge(no, nxt, nxt+1);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, p, q, root, Q, k, ans;
	cin >> n >> root;
	root--;
	
	for (int i = 0; i < n; i++)
	{
		cin >> cost[i];
	}
	
	int u, v;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	h[root] = -1;
	dfs(root, root);
	
	build(1, 0, n-1);
	
	//~ cout << "euler = ";
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << euler[i] << ' ';
	//~ }
	//~ cout << endl;
	
	ll lst = 0;
	cin >> Q;
	for (int i = 0; i < Q; i++)
	{
		cin >> p >> q;
		x = ((p + lst) % n);
		k = (q + lst) % n;
		
		//~ printf("consultando subtree do %lld [%lld, %lld]  k = %lld\n", x, ini[x], fim[x], k);
		ans = query(1, 0, n-1, ini[x], fim[x], k);
		cout << ans << "\n";
		lst = ans;
	}
	
	
	
	
	return 0;
}
