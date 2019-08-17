#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
#define mp make_pair
#define pb push_back

bool cut[MAXN];
int n, d[MAXN], low[MAXN], seen[MAXN], vcorte, tempo, root;
string name[MAXN];
map<string, int> mapa;
vector<int> g[MAXN];


void reset(){
	for (int i = 0; i <= n; i++)
	{
		cut[i] = false;
		g[i].clear();
		seen[i] = d[i] = low[i] = 0;
	}
	tempo = 1;
	vcorte = 0;
	mapa.clear();
}

void dfs(int u, int pai){
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	bool any = false;
	int nf = 0;
	
	for(int v : g[u]){
		if(!seen[v]){
			
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			nf++;
			if(d[u] <= low[v]) any = true;
			
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
	
	if(root == u && nf >= 2){
		vcorte++;
		cut[u] = true;
	}
	
	if(root != u && any){
		vcorte++;
		cut[u] = true;
	}
	
	
}

int main(){
	bool fst = true;
	int m, u, v, caso = 1;
	string A, B;
	
	while (cin >> n, n)
	{
		if(!fst) cout << "\n";
		fst = false;
		reset();
		for (int i = 1; i <= n; i++)
		{
			cin >> name[i];
			mapa[name[i]] = i;
		}
		cin >> m;
		while (m--)
		{
			cin >> A >> B;
			u = mapa[A];
			v = mapa[B];
			g[u].pb(v);
			g[v].pb(u);
		}
		
		for (int i = 1; i <= n; i++)
			if(!seen[i]){
				root = i;
				dfs(i, i);
			}
		
		vector<string> saida;
		cout << "City map #" << caso++ << ": " << vcorte << " camera(s) found\n";
		for (int i = 1; i <= n; i++)
			if(cut[i])
				saida.pb(name[i]);
				
		sort(saida.begin(), saida.end());
		for(string s : saida)
			cout << s << "\n";
	}
	
	
	
	return 0;
}
