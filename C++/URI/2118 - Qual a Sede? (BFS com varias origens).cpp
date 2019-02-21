#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef long double ld;
#define EPS 1e-9
#define PI acos(-1)
#define INF 10000000
#define MAXN 101010
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

struct sede{
	int id, medal, idade;
	sede(){}
	sede(int _id, int _medal, int _idade){
		id = _id;
		medal = _medal;
		idade = _idade;
	}
};

bool melhor(sede a, sede b){
	if(a.medal == b.medal) return a.idade > b.idade;
	return a.medal > b.medal;
}

int n, m, q, qtdSede;
sede vet[MAXN];
int pai[MAXN];
vector<int> g[MAXN];
char vis[MAXN];
int dist[MAXN];
char tem[MAXN];
int ans[MAXN];


void bfs(){
	queue<pair<int, int> > q;
	for (int i = 0; i < n; i++)
	{
		dist[i] = INF;
		pai[i] = -1;
		vis[i] = 0;
		if(tem[i]){
			q.push(mp(0, i));
			pai[i] = i;
			ans[i] = i;
			dist[i] = 0;
			//~ printf("botando %d na fila\n", i+1);
		}
	}
	
	int u, v, qtd;
	while (!q.empty())
	{
		qtd = q.front().F;
		u = q.front().S;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		
		for (int i = 0; i < (int)g[u].size(); i++)
		{
			v = g[u][i];
			if(dist[u] + 1 < dist[v]){
				dist[v] = dist[u] + 1;
				pai[v] = pai[u];
				q.push(mp(dist[v], v));
			}else if(dist[u] + 1 == dist[v]){
				if(melhor(vet[pai[u]], vet[pai[v]])){
					pai[v] = pai[u];
					q.push(mp(dist[v], v));
				}
			}
		}
		
	}
	
}

void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
		tem[i] = 0;
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int id, qtdMedalha, idade;
	while (cin >> n >> qtdSede >> q >> m)
	{
		reset();
		for (int i = 0; i < qtdSede; i++)
		{
			cin >> id >> qtdMedalha >> idade;
			id--;
			if(tem[id]){
				if(melhor(sede(i, qtdMedalha, idade), vet[id])){
					vet[id] = sede(i, qtdMedalha, idade);
				}
			}else{
				vet[id] = sede(i, qtdMedalha, idade);
				tem[id] = 1;
			}
		}
		int u, v;
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v;
			u--;v--;
			g[u].pb(v);
			g[v].pb(u);
		}
		
		bfs();
		for (int i = 0; i < q; i++)
		{
			cin >> u;
			u--;
			if(pai[u] == -1) cout << "Noic\n";
			else cout << vet[pai[u]].id + 1 << "\n";
		}
		
	}
	
	
	
	
	return 0;
}
