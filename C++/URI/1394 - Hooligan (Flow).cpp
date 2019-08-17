#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXM 101010
#define MAXN 2000
#define INF 1e9

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
int cur;
int n, M, games;
int jogos[MAXN];
int pts[MAXN];
int seen[MAXN];
int qtd[41][41];
int MX, maxPt;
int tempo;

void reset(){
	memset(qtd, 0, sizeof qtd);
	memset(jogos, 0, sizeof jogos);
	memset(pts, 0, sizeof pts);
	
	MX = 0;
	cur = 0;
	for (int i = 0; i < MAXN; i++)
	{
		g[i].clear();
	}
}

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

void build(){
	int src = MAXN - 1;
	int sink = MAXN - 2;
	
	int cnt = n+1;
	for (int i = 1; i < n; i++)
	{
		add_edge(i, sink, maxPt - pts[i] - 1, 0);
		//~ printf("adicionando aresta de %d para sink com cap %d\n", i, maxPt - pts[i] - 1);
		for (int j = i+1; j < n; j++)
		{
			add_edge(src, cnt, (M - qtd[i][j])*2, 0);
			//~ printf("adicionando aresta de src para (%d, %d) com cap %d\n", i, j, (M - qtd[i][j])*2);
			
			MX += (M - qtd[i][j])*2;
			
			add_edge(cnt, i, INF, 0);
			//~ printf("adicionando aresta de (%d, %d) para %d com cap INF\n", i, j, i);
			add_edge(cnt, j, INF, 0);
			//~ printf("adicionando aresta de (%d, %d) para %d com cap INF\n", i, j, j);
			cnt++;
		}
	}
}

string solve(){
	int src = MAXN - 1;
	int sink = MAXN - 2;
	
	//~ printf("MX = %d\n", MX);
	
	int f = mf(src, sink);
	//~ printf("fluxo maximo = %d\n", f);
	if(f == MX) return "Y";
	return "N";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t1, t2;
	char op;
	while(cin >> n >> M >> games){
		if(n==0 && M==0 && games==0) break;
		reset();
		for (int i = 0; i < games; i++)
		{
			cin >> t1 >> op >> t2;
			if(op == '>') pts[t1] += 2;
			if(op == '<') pts[t2] += 2;
			if(op == '='){
				pts[t1]++;
				pts[t2]++;
			}
			
			qtd[min(t1, t2)][max(t1, t2)]++;
			
			jogos[t1]++;
			jogos[t2]++;
		}
		
		//~ printf("pts[0] = %d\n", pts[0]);
		maxPt = pts[0] + ((n-1)*M - jogos[0])*2;
		//~ printf("%d + %d = %d\n", pts[0], ((n-1)*M - jogos[0])*2, maxPt);
		//~ printf("maxPt = %d\n", maxPt);
		
		bool erro = false;
		for (int i = 1; i < n; i++)
		{
			if(pts[i] >= maxPt){
				erro = true;
			}
		}
		
		if(erro){
			cout << "N\n";
			continue;
		}
		build();
		
		cout << solve() << "\n";
	}
	
	
	return 0;
}
