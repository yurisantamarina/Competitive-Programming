//~ http://codeforces.com/gym/100676

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define mp make_pair
#define F first
#define S second
#define pb push_back

typedef long long int ll;
vector<pair<ll, ll> > g[MAXN], tr[MAXN];

ll n, seen[MAXN], d[MAXN], low[MAXN], in[MAXN], out[MAXN], tempo, comp[MAXN];
map<pair<ll, ll>, ll> mapa;
stack<ll> p;

void dfsTarjan(ll u, ll pai, bool flag){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	if(flag)
		p.push(u);
	
	for(pair<ll, ll> pp : g[u]){
		ll v = pp.F;
		ll w = pp.S;
		
		if(!seen[v]){
			dfsTarjan(v, u, flag);
			low[u] = min(low[u], low[v]);
			
			if(d[u] < low[v]){
				if(flag){
					while(!p.empty()){
						ll x = p.top();
						comp[x] = v;
						p.pop();
						if(x == v) break;
					}
				}else{
					tr[comp[u]].pb(mp(comp[v], w));
					tr[comp[v]].pb(mp(comp[u], w));
				}
			}
		}else{
			if(v != pai)
				low[u] = min(low[u], d[v]);
		}
	}
}

void dfsIn(ll u, ll pai){
	in[u] = 0;
	
	for(pair<ll, ll> pp : tr[u]){
		ll v = pp.F;
		ll w = pp.S;
		
		if(v == pai) continue;
		dfsIn(v, u);
		in[u] = max(in[u], w + in[v]);
	}
}

void dfsOut(ll u, ll pai){
	ll mx1 = -LLONG_MAX, mx2 = -LLONG_MAX;
	
	for(pair<ll, ll> pp : tr[u]){
		ll v = pp.F;
		ll w = pp.S;
		
		if(v == pai) continue;
		if(in[v]+w >= mx1){
			mx2 = mx1;
			mx1 = in[v]+w;
		}else if(in[v]+w > mx2){
			mx2 = in[v]+w;
		}
	}
	
	for(pair<ll, ll> pp : tr[u]){
		ll v = pp.F;
		ll w = pp.S;
		
		if(v == pai) continue;
		
		ll at = mx1 == in[v]+w ? mx2 : mx1;
		out[v] = max(out[v], at+w);
		out[v] = max(out[v], w + out[u]);
		
		dfsOut(v, u);
	}
}

void reset(){
	for (ll i = 0; i <= n; i++)
	{
		g[i].clear();
		tr[i].clear();
		seen[i] = 0;
		in[i] = 0;
		out[i] = 0;
	}
	mapa.clear();
	while(!p.empty()) p.pop();
}

int main(){
	ll tc, m, u, v, w;
	scanf("%lld", &tc);
	while (tc--)
	{
		scanf("%lld %lld", &n, &m);
		reset();
		for (ll i = 0; i < m; i++)
		{
			scanf("%lld %lld %lld", &u, &v, &w);
			if(u == v) continue;
			g[u].pb(mp(v, w));
			g[v].pb(mp(u, w));
		}
		memset(seen, 0, sizeof seen);
		dfsTarjan(1, 1, true);
		while(!p.empty()){
			comp[p.top()] = 1;
			p.pop();
		}
		
		memset(seen, 0, sizeof seen);
		dfsTarjan(1, 1, false);
		
		dfsIn(1, 1);
		out[1] = 0;
		dfsOut(1, 1);
		
		ll ans = LLONG_MAX, capital = 0;
		for(ll i = 1; i <= n; i++){
			w = max(in[comp[i]], out[comp[i]]);
			if(w < ans){
				ans = w;
				capital = i;
			}
		}
		
		printf("%lld %lld\n", capital, ans);
	}
	
	
	return 0;
}
