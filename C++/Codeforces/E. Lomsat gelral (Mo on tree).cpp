#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define MAXN 100010
#define block 250
typedef long long int ll;


struct query{
	ll l, r, id;
	query(){}
	query(ll _l, ll _r, ll _id){
		l = _l;
		r = _r;
		id = _id;
	}
	
	bool operator < (query other) const{
		if(l / block == other.l / block) return r < other.r;
		return l/block < other.l/block;
	}
};

ll ans[MAXN];
ll mx=0;
ll f[MAXN];
ll sum[MAXN];
ll ini[MAXN];
ll tam[MAXN];
ll color[MAXN];
vector<ll> vet;
vector<query> queries;
vector<ll> g[MAXN];

void dfs(ll u, ll pai){
	ini[u] = (ll)vet.size();
	vet.pb(color[u]);
	tam[u] = 1;
	
	for (ll v : g[u])
	{
		if(v == pai) continue;
		dfs(v, u);
		tam[u] += tam[v];
	}
}

void add(ll pos){
	ll cor = vet[pos];
	sum[f[cor]] -= cor;
	f[cor]++;
	sum[f[cor]] += cor;
	mx = max(mx, f[cor]);
}

void del(ll pos){
	ll cor = vet[pos];
	sum[f[cor]] -= cor;
	f[cor]--;
	sum[f[cor]] += cor;
	if(sum[f[cor]+1] == 0 && f[cor]+1 == mx){
		mx--;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, u, v;
	cin >> n;
	for (ll i = 0; i < n; i++)
	{
		cin >> color[i];
	}
	for (ll i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	dfs(0, 0);
	for (ll i = 0; i < n; i++)
	{
		queries.pb(query(ini[i], ini[i] + tam[i] - 1, i));
	}
	
	sort(queries.begin(), queries.end());
	
	ll L = 0, R = 0;
	ll l, r;
	for (ll i = 0; i < n; i++)
	{
		l = queries[i].l;
		r = queries[i].r;
		
		while (R <= r)
		{
			add(R++);
		}
		while (R > r+1)
		{
			del(--R);
		}
		while (L < l)
		{
			del(L++);
		}
		while (L > l)
		{
			add(--L);
		}
		ans[queries[i].id] = sum[mx];
	}
	for (ll i = 0; i < n; i++)
	{
		cout << ans[i] << " ";
	}
	cout << "\n";
	
	
	
	return 0;
}
