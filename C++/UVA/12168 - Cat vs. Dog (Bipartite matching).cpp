#include <bits/stdc++.h>

using namespace std;
#define MAXN 510
#define MAXM 1010100
#define mp make_pair
#define pb push_back

struct person{
	int id, op1, op2;
	person(){}
	person(int _id, int _op1, int _op2){
		id = _id;
		op1 = _op1;
		op2 = _op2;
	}
};

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
int tempo;
int seen[MAXN];
vector<person> catLover, dogLover;
int src=0, sink=1;
int n, qtdCat, qtdDog;

bool conflito(person cat, person dog){
	if(cat.op1 == dog.op2 || cat.op2 == dog.op1) return true;
	return false;
}

void add_edge(int u, int v, int cap, int rcap){
	ed[cur] = edge(v, 0, cap);
	g[u].pb(cur++);
	
	ed[cur] = edge(u, 0, rcap);
	g[v].pb(cur++);
}

void reset(){
	cur = 0;
	for (int i = 0; i < n+3; i++)
	{
		g[i].clear();
	}
	catLover.clear();
	dogLover.clear();
}

int dfs(int at, int mn){
	if(at == sink) return mn;
	
	int idx, v, cap;
	for (int i = 0; i < (int)g[at].size(); i++)
	{
		idx = g[at][i];
		v = ed[idx].to;
		cap = ed[idx].c - ed[idx].f;
		
		if(seen[v] < tempo && cap > 0){
			seen[v] = tempo;
			if(int a = dfs(v, min(mn, cap))){
				ed[idx].f += a;
				ed[idx^1].f -= a;
				return a;
			}
		}
	}
	return 0;
}

int mf(){
	memset(seen, 0, sizeof seen);
	tempo = 1;
	int flow = 0;
	while (int a = dfs(src, INT_MAX))
	{
		flow += a;
		tempo++;
	}
	
	return flow;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc;
	cin >> tc;
	int id1, id2;
	char c1, c2;
	while (tc--)
	{
		cin >> qtdCat >> qtdDog >> n;
		reset();
		
		for (int i = 2; i < n+2; i++)
		{
			cin >> c1 >> id1 >> c2 >> id2;
			if(c1 == 'C'){
				catLover.pb(person(i, id1, id2));
				add_edge(src, i, 1, 0);
			}else{
				dogLover.pb(person(i, id1, id2));
				add_edge(i, sink, 1, 0);
			}
		}
		
		for (int i = 0; i < (int)catLover.size(); i++)
		{
			for (int j = 0; j < (int)dogLover.size(); j++)
			{
				if(conflito(catLover[i], dogLover[j])){
					add_edge(catLover[i].id, dogLover[j].id, 1, 0);
				}
			}
		}
		
		cout << n - mf() << "\n";
	}
	
	
	
	return 0;
}
