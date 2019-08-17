#include <bits/stdc++.h>

using namespace std;

#define MAXM 14400
#define MAXN 60
#define F first
#define S second
#define mp make_pair
#define pb push_back

struct edge{
	int to, f, c;
	edge(){}
	edge(int _to, int _f, int _c){
		to = _to;
		f = _f;
		c = _c;
	}
};

edge ed[MAXM];
vector<int> g[MAXN];
int cur, tempo;
int seen[MAXN];
vector<string> acc[29];
string ans[29];
int n, q;

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

int dfs(int at, int sink, int mn){
	if(at == sink) return mn;
	
	int idx, v, cap;
	for (int i = 0; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
			seen[v] = tempo;
			if(int a = dfs(v, sink, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	return 0;
}

int mf(int src, int sink){
	int flow = 0;
	tempo = 1;
	memset(seen, 0, sizeof seen);
	
	while (int a = dfs(src, sink, INT_MAX))
	{
		flow += a;
		tempo++;
	}
	
	
	return flow;
}

string transform(string s){
	s[0] = toupper(s[0]);
	
	for (int i = 1; i < (int)s.size(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

string find(int id, char c){
	for (int i = 0; i < (int)acc[id].size(); i++)
	{
		if(acc[id][i][0] == c) return acc[id][i];
	}
}

void recover(){
	
	int idx;
	for (int at = 2; at < n+2; at++)
	{
		for (int i = 0; i < (int)g[at].size(); i++)
		{
			idx = g[at][i];
			if(idx%2!=0) continue;
			
			if(ed[idx].f == 1){
				ans[ed[idx].to - (n + 2)] = find(at, ed[idx].to - (n + 2) + 'A');
				//~ printf("achei matching de %d com %d\n", at-2, ed[idx].to - (n + 2));
				break;
			}
		}
	}
	
}

void reset(){
	cur = 0;
	for (int i = 0; i < 29; i++)
	{
		acc[i].clear();
		
	}
	for (int i = 0; i < 60; i++)
	{
		g[i].clear();
	}
	
	
	
}

int main(){
	int tc, caso = 1, src, sink, q;
	string s;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		reset();
		src = 0;
		sink = 1;
		for (int i = 0; i < 26; i++)
		{
			add_edge(i + n + 2, sink, 1, 0);
			//~ printf("ligando %d em %d\n", i+n+2, sink);
		}
		
		for (int i = 2; i < n+2; i++)
		{
			cin >> q;
			add_edge(src, i, 1, 0);
			//~ printf("ligando %d em %d\n", src, i);
			while (q--)
			{
				cin >> s;
				s = transform(s);
				acc[i].pb(s);
				
				if(s[0] - 'A' >= n) continue;
				add_edge(i, s[0] - 'A' + n + 2, 1, 0);
				//~ printf("ligando %d em %d\n", i, s[0] - 'A' + n + 2);
			}
			
		}
		
		int aux = mf(src, sink);
		//~ printf("mf = %d\n", aux);
		cout << "Case #" << caso++ << ":\n";
		recover();
		for (int i = 0; i < n; i++)
		{
			cout << ans[i] << "\n";
		}
		
	}
	
	
	return 0;
}
