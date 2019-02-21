#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const ll dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const ll dy[] = {-1,0,0, 1,1, 1,-1,-1};
ll gcd (ll x, ll y) {return (y != 0 ? gcd (y, x%y) : x);}
ll lcm (ll x, ll y) {return (x / gcd (x, y) * y);}
#define MAXN 1500
int res[MAXN][MAXN];
vi g[MAXN];
int parent[MAXN];
char vis[MAXN];

bool bfs(int src, int sink){
	queue<int> q;
	q.push(src);
	vis[src]=1;
	parent[src]=src;
	
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if(u==sink) return true;
		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			if(res[u][v] > 0 && !vis[v]){
				vis[v] = 1;
				q.push(v);
				parent[v] = u;
			}
		}		
	}	
	return false;
}

int augment(int sink){
	int bottleneck = 1e8;
	int u = sink;
	while (u!=parent[u])
	{
		if(res[parent[u]][u] < bottleneck) bottleneck = res[parent[u]][u];
		u = parent[u];
	}
	u = sink;
	
	while (u!=parent[u])
	{
		res[parent[u]][u]-=bottleneck;
		res[u][parent[u]]+=bottleneck;
		u = parent[u];
	}
	return bottleneck;//para incrementar no maxflow
}

int maxFlow(int src, int sink){
	int mf=0;
	while (1)
	{
		memset(parent, -1, sizeof parent);
		memset(vis, 0, sizeof vis);
		if(bfs(src, sink)){// a bfs vai preencher o vetor parent e se tiver caminho retorna true. Se tiver caminho, vai percorrer ele em augment pra achar o gargalo
			mf += augment(sink);
		}else break;
	}
	return mf;
}

void limpa(){
	for (int i = 0; i < MAXN; i++)
	{
		g[i].clear();
		memset(res[i], 0, sizeof res[i]);
	}
}

void addEdge(int u, int v, int cap){
	g[u].pb(v);
	g[v].pb(u);
	res[u][v] = cap;
	res[v][u] = 0;
}

int main () {
	int a, b;
	int x, q;
	int src=MAXN-1, sink=MAXN-2;
	while (cin >> a >> b, a!=0)
	{
		limpa();
		int sum=0;
		for (int i = 0; i < a; i++)
		{
			cin >> x;
			addEdge(i+b, sink, x);
			sum+=x;
			//~ cout << "aresta " << i+b << " sink " << " = " << x << endl;
		}
		
		for (int i = 0; i < b; i++)
		{
			addEdge(src, i, 1);
			//~ cout << "aresta src " << i << " = " << 1 << endl;
			cin >> q;
			while (q--)
			{
				cin >> x;
				//~ cout << "aresta " << i << " " << x+b-1 << " = " << x << endl;
				addEdge(i, x+b-1, 1);
			}
		}
		
		int mf = maxFlow(src, sink);
		if(mf<sum) cout << 0 << "\n";
		else{
			bool fst;
			cout << 1 << "\n";
			for (int u = 0+b; u < a+b; u++)
			{
				fst=true;
				for (int i = 0; i < g[u].size(); i++)
				{
					int v = g[u][i];
					if(res[u][v] > 0){
						if(!fst) cout << " ";
						fst=false;
						cout << v+1;
					}
				}
				cout << "\n";
			}
			
		}
	}
	
	
	
	return 0;
}
