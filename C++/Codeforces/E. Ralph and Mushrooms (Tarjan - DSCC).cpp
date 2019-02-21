#include <bits/stdc++.h>

using namespace std;
#define MAXN 1001010
#define pb push_back
#define F first
#define S second
typedef long long int ll;
typedef pair<ll, ll> pii;

ll f1[MAXN], f2[MAXN], dp[MAXN];
ll sz, d[MAXN], low[MAXN], seen[MAXN], tempo = 1, peso[MAXN], comp[MAXN], n, sccCounter = 1;
vector<pii> g[MAXN], tr[MAXN];
stack<ll> p;

void buildF(){
	f1[1] = 1;
	f2[1] = 1;
	
	for(ll i = 2; i < MAXN; i++){
		f1[i] = f1[i-1] + i;
		f2[i] = f2[i-1] + f1[i];
		if(f1[i] >= 1e8){
			sz = i - 1;
			break;
		}
		//~ prllf("i = %lld  f1[i] = %lld  f2[i] = %lld\n", i, f1[i], f2[i]);
	}
}

ll getPeso(ll x){
	ll pos = lower_bound(f1 + 1, f1 + 1 + sz, x) - f1;
	//~ prllf("x = %d   pos = %d\n", x, pos);
	if(f1[pos] != x) pos--;
	
	return ((ll)pos + 1) * x - f2[pos];
}

void dfs(ll u){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	p.push(u);
	for(pii pp : g[u]){
		ll v = pp.F;
		if(!seen[v]){
			dfs(v);
			low[u] = min(low[u], low[v]);
		}else low[u] = min(low[u], d[v]);
	}
	
	if(low[u] < d[u]) return;
	
	while(!p.empty()){
		ll x = p.top(); p.pop();
		comp[x] = sccCounter;
		d[x] = 1e9;
		if(x == u) break;
	}
	
	sccCounter++;
}

void buildDSCC(){
	for(ll u = 1; u <= n; u++)
		for(pii pp : g[u]){
			ll v = pp.F;
			ll w = pp.S;
			if(comp[u] != comp[v]){
				tr[comp[u]].pb({comp[v], w});
			}else{
				//~ prllf("pesooo = %lld\n", getPeso(w));
				peso[comp[u]] += getPeso(w);
			}
		}
}

ll solve(ll u){
	if(seen[u]) return dp[u];
	seen[u] = 1;
	
	for(pii pp : tr[u]){
		ll v = pp.F;
		ll w = pp.S;
		
		dp[u] = max(dp[u], w + solve(v));
	}
	
	return dp[u] = dp[u] + peso[u];
}

int main(){
	buildF();
	ll u, v, w, m, src;
	scanf("%lld %lld", &n, &m);
	for (ll i = 0; i < m; i++)
	{
		scanf("%lld %lld %lld", &u, &v, &w);
		g[u].pb({v, w});
	}
	scanf("%lld", &src);
	
	for(ll i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i);
	
	buildDSCC();
	
	src = comp[src];
	
	memset(seen, 0, sizeof seen);
	printf("%lld\n", solve(src));
	
	//~ prllf("%d sccs\n", sccCounter - 1);
	//~ for(ll i = 1; i < sccCounter; i++)
		//~ prllf("peso[%d] = %d\n", i, peso[i]);
		
	return 0;
}
