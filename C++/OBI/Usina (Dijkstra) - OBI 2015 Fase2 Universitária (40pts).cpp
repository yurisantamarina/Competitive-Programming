#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
#define MAXN 100010
#define ll long long 

ll n, m, maxDist, qtd;
char has[MAXN];
vector<pair<ll, ll> > g[MAXN];
ll dist[MAXN];
char vis[MAXN];

ll dij(){
	priority_queue<pair<ll, ll> > pq;
	for (ll i = 0; i <= n; i++)
	{
		dist[i] = 1000000000000000000LL;
		vis[i] = 0;
	}
	pq.push(mp(0, 0));
	dist[0] = 0LL;
	
	ll u;
	while (!pq.empty())
	{
		u = pq.top().S;
		pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		
		for (ll i = 0; i < g[u].size(); i++)
		{
			ll v = g[u][i].F;
			ll w = g[u][i].S;
			
			if(has[v]){
				if(max(dist[u] + w - maxDist, 0LL) < dist[v]){
					dist[v] = max(dist[u] + w - maxDist, 0LL);
					pq.push(mp(-dist[v], v));
				}
			}else{
				if(dist[u] + w < dist[v]){
					dist[v] = dist[u] + w;
					pq.push(mp(-dist[v], v));
				}
			}
		}
		
	}
	
	return dist[n-1]==1000000000000000000LL ? -1 : dist[n-1];
}

int main () {
	ll x;
	memset(has, 0, sizeof has);
	cin >> n >> m >> qtd >> maxDist;
	for (ll i = 0; i < qtd; i++)
	{
		cin >> x;
		x--;
		has[x] = 1;
	}
	
	ll u, v, w;
	for (ll i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		u--; v--;
		g[u].pb(mp(v, w));
	}
	
	cout << dij() << "\n";
	
	
	
	
	return 0;
}
