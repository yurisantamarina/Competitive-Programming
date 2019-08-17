#include <bits/stdc++.h>


using namespace std;
typedef long long int ll;
#define ABRE 0
#define FECHA 1
#define MAXN 40010
#define pb push_back

struct pv{
	ll x, y;
	pv(){}
	pv(ll _x, ll _y){
		x = _x;
		y = _y;
	}
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
};

struct event{
	pv p;
	int tipo, id;
	event(){}
	event(pv _p, int _tipo, int _id){
		p = _p; tipo = _tipo; id = _id;
	}
	
	bool operator < (event other) const{
		if(p.x == other.p.x){
			if(tipo == other.tipo){
				if(tipo == ABRE) return p.y < other.p.y;
				return p.y > other.p.y;
			}
			return tipo < other.tipo;
		}
		return p.x < other.p.x;
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};

vector<seg> segmento;

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

ll func(pv a, pv b, pv c){
	return cross(b-a, c-b);
}

bool compare(int _1, int _2){
	pv a = segmento[_1].a;
	pv b = segmento[_1].b;
	pv c = segmento[_2].a;
	pv d = segmento[_2].b;
	
	if(a.x <= c.x){
		if(func(a, c, b) > 0) return true;
		return false;
	}else{
		if(func(c, a, d) > 0) return false;
		return true;
	}
}

int n;
int v[MAXN];
vector<event> evento;

vector<int> g[MAXN];
char vis[MAXN];
set<int, bool(*)(int, int)> ativo(compare);
set<int, bool(*)(int, int)>::iterator it;

void dfs(int u){
	if(vis[u]) return;
	vis[u] = 1;
	
	for (int i = 0; i < g[u].size(); i++)
	{
		if(!vis[g[u][i]]) dfs(g[u][i]);
		v[u] += v[g[u][i]];
	}
}

int getTopo(){
	if(ativo.size()==0) return MAXN-1;
	return *ativo.begin();
}

bool mudou(int segAt){
	int nw = getTopo();
	return nw != segAt;
}

void bota(int id){
	//~ printf("inserindo %d\n", id+1);
	ativo.insert(id);
	if(segmento[id].a.y < segmento[id].b.y){
		it = ativo.find(id);
		it++;
		if(it!=ativo.end()){
			g[*it].pb(id);
		}
	}
}

void tira(int id){
	
	if(segmento[id].a.y > segmento[id].b.y){
		it = ativo.find(id);
		it++;
		if(it!=ativo.end()){
			g[*it].pb(id);
		}
	}
	//~ printf("removendo %d\n", id+1);
	ativo.erase(id);
}

void sweep(){
	sort(evento.begin(), evento.end());
	memset(v, 0, sizeof v);
	int segAt = getTopo();
	int xlst = -1;
	int xat = -1;
	for (int i = 0; i < evento.size(); i++)
	{
		//~ cout << endl;
		xat = evento[i].p.x;
		if(evento[i].tipo == ABRE) bota(evento[i].id);
		else tira(evento[i].id);
		//~ printf("Topo Atual = %d\n", getTopo()+1);
		//~ for(auto ii : ativo) cout << ii+1 << " ";
		//~ cout << endl;
		
		if(mudou(segAt)){
			v[segAt] += (xat - xlst);
			//~ printf("Somando %d no %d\n", (xat-xlst), segAt+1);
			xlst = xat;
			segAt = getTopo();
		}
	}
}

void reset(){
	segmento.clear();
	evento.clear();
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc;
	cin >> tc;
	while(tc--){
		reset();
		cin >> n;
		ll x1, y1, x2, y2;
		for (int i = 0; i < n; i++)
		{
			cin >> x1 >> y1 >> x2 >> y2;
			segmento.pb(seg(pv(x1, y1), pv(x2, y2)));
			evento.pb(event(pv(x1, y1), ABRE, i));
			evento.pb(event(pv(x2, y2), FECHA, i));
		}
		sweep();
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < n; i++)
		{
			if(!vis[i]) dfs(i);
			cout << v[i] << "\n";
		}
		
	}
	
	
	
	return 0;
}
