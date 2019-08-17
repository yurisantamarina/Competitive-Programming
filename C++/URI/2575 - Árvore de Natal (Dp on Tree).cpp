#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 1000010

int read_int(){
	char r;
	bool start=false,neg=false;
	int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}

struct edge{
	int v, w, id;
	edge(){}
	edge(int a, int b, int c){
		v = a;
		w = b;
		id = c;
	}
};
int buniteza[MAXN];
vector<edge> g[MAXN];
int cost[MAXN];
vector<int> saida;

inline void dfs(int u, int pai){
	
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i].v == pai) continue;
		cost[g[u][i].v] = g[u][i].w;
		dfs(g[u][i].v, u);
	
		buniteza[u] += max(buniteza[g[u][i].v], 0);
	}
	buniteza[u] += cost[u];
	//~ printf("Estou em %d  cost = %d  buniteza = %d\n", u, cost[u], buniteza[u]);
	if(buniteza[u] < 0) buniteza[u] = 0;
	
}

inline void dfs2(int u, int pai){
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i].v == pai) continue;
		if(buniteza[g[u][i].v] == 0){
			saida.pb(g[u][i].id);
		}else dfs2(g[u][i].v, u);
		
	}
	
	
}

int main () {
	
	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	int n;
	n = read_int();
	//~ cin >> n;
	int u, v, w;
	int id;
	for (int i = 0; i < n-1; i++)
	{
		//~ cin >> id >> u >> v >> w;
		id = read_int();
		u = read_int();
		v = read_int();
		w = read_int();
		//~ u--; v--;
		g[u].emplace_back(edge(v, w, id));
		g[v].emplace_back(edge(u, w, id));
	}
	dfs(0, 0);
	dfs2(0, 0);
	
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << i << " :";
		//~ cout << cost[i] << "  " << buniteza[i] << endl;
	//~ }
	
	sort(saida.begin(), saida.end());
	//~ cout << buniteza[0] << " " << saida.size() << "\n";
	printf("%d %d\n", buniteza[0], (int)saida.size());
	for (int i = 0; i < saida.size(); i++)
	{
		if(i) printf(" ");
		printf("%d", saida[i]);
		//~ cout << saida[i];
	}
	if(saida.size()) printf("\n");
	
	
		
	return 0;
}
