#include <bits/stdc++.h>

using namespace std;
#define MAXM 1010100
#define MAXN 10101
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define INF 1e9

struct edge{
	int to, f, c, cost;
	edge(){}
	edge(int _to, int _f, int _c, int _cost){
		to = _to;
		f = _f;
		c = _c;
		cost = _cost;
	}
};

edge ed[MAXM];
vector<int> g[MAXN];
int cur;
char inq[MAXN];
int dist[MAXN];
int freq[29];
int n;
pair<int, int> pai[MAXN];


void add_edge(int u, int v, int cap, int rcap, int cost){
	ed[cur] = edge(v, 0, cap, cost);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap, -cost);
	g[v].pb(cur++);
}

void build(string s, int mx, int id){
	add_edge(0, id, mx, 0, 0);
	memset(freq, 0, sizeof freq);
	
	//~ printf("aresta de src %d para %d com %d\n", 0, id, mx);
	for (int i = 0; i < (int)s.size(); i++)
	{
		freq[s[i]-'a']++;
	}
	
	for (int i = 0; i < 26; i++)
	{
		if(freq[i]){
			add_edge(id, i+n+1, freq[i], 0, id);
			//~ printf("aresta de %d para %d com %d\n", id, i+n+1, freq[i]);
		}
	}
}

bool spfa(int src, int sink){
	queue<int> q;
	memset(inq, 0, sizeof inq);
	for (int i = 0; i < n+30; i++)
	{
		dist[i] = INF;
	}
	
	q.push(src);
	inq[src] = 0;
	dist[src] = 0;
	
	int u, v, cost, cap, idx;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		
		inq[u] = 0;
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			idx = g[u][i];
			v = ed[idx].to;
			cap = ed[idx].c - ed[idx].f;
			cost = ed[idx].cost;
			
			if(dist[u] + cost < dist[v] && cap){
				dist[v] = dist[u] + cost;
				pai[v] = mp(u, idx);
				if(!inq[v]){
					q.push(v);
					inq[v] = 1;
				}
			}
		}
		
	}
	
	return dist[sink]!=INF;
}

pair<int, int> augment(int src, int sink){
	int mn = INF;
	int cost = 0;
	int u, cap, idx;
	
	u = sink;
	while (u!=src)
	{
		idx = pai[u].S;
		cap = ed[idx].c - ed[idx].f;
		mn = min(mn, cap);
		u = pai[u].F;
	}
	
	u = sink;
	while (u!=src)
	{
		idx = pai[u].S;
		ed[idx].f+=mn;
		ed[idx^1].f-=mn;
		cost += (ed[idx].cost * mn);
		u = pai[u].F;
	}
	
	
	
	return mp(mn, cost);
}

pair<int, int> mcmf(int src, int sink){
	pair<int, int> ans = mp(0, 0);
	pair<int, int> aux;
	
	while (spfa(src, sink))
	{
		aux = augment(src, sink);
		ans.F += aux.F;
		ans.S += aux.S;
	}
	
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string quero;
	cin >> quero;
	memset(freq, 0, sizeof freq);
	for (int i = 0; i < (int)quero.size(); i++)
	{
		freq[quero[i] - 'a']++;
	}
	
	cin >> n;
	int src = 0, sink = n+27;
	for (int i = 0; i < 26; i++)
	{
		if(freq[i]){
			add_edge(i+n+1, sink, freq[i], 0, 0);
			//~ printf("aresta de %d para sink %d com freq %d\n", i+n+1, sink, freq[i]);
		}
	}
	
	
	string s;
	int mx;
	
	
	for (int i = 0; i < n; i++)
	{
		cin >> s >> mx;
		build(s, mx, i+1);
	}
	
	
	
	
	pair<int, int> ans = mcmf(src, sink);
	if(ans.F == (int)quero.size()){
		cout << ans.S << "\n";
	}else{
		cout << "-1\n";
	}
	
	return 0;
}
