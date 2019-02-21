#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define ABRE 0
#define CONSULTA 1
#define FECHA 2
#define pb push_back
#define MAXN 100010

struct pv{
	ll x, y;
	pv(){}
	pv(ll _x,ll _y){
		x = _x;
		y = _y;
	}
	pv operator - (pv other){
		return pv(x-other.x, y - other.y);
	}
};

struct segmento{
	pv a, b;
	segmento(){}
	segmento(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};

struct event{
	pv p;
	int tipo, id;
	event(pv _p, int _tipo, int _id){
		p = _p;
		tipo = _tipo;
		id = _id;
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

vector<segmento> seg;
vector<event> evento;
vector<int> g[MAXN];

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

ll func(pv a, pv b, pv c){
	return cross(b-a, c-b);
}

bool compare(int _1, int _2){
	pv a = seg[_1].a;
	pv b = seg[_1].b;
	pv c = seg[_2].a;
	pv d = seg[_2].b;
	if(a.x <= c.x){
		if(func(a, c, b) > 0) return true;
		return false;
	}else{
		if(func(c, a, d) > 0) return false;
		return true;
	}
}

set<int, bool(*)(int, int)> ativo(compare);
set<int, bool(*)(int, int)>::iterator it;


void bota(int id){
	ativo.insert(id);
	if(seg[id].a.y < seg[id].b.y){
		it = ativo.find(id);
		it++;
		if(it!=ativo.end()){
			g[id].pb(*it);
		}
	}
}

void tira(int id){
	if(seg[id].a.y > seg[id].b.y){
		it = ativo.find(id);
		it++;
		if(it!=ativo.end()){
			g[id].pb(*it);
		}
	}
	ativo.erase(id);
}

void consulta(int id){
	if(ativo.size() > 0){
		g[id].pb(*ativo.begin());
	}
}

int dfs(int u){
	if(g[u].size() == 0) return u;
	int aux;
	for (int i = 0; i < g[u].size(); i++)
	{
		aux = dfs(g[u][i]);
	}
	return aux;
}

void sweep(){
	sort(evento.begin(), evento.end());
	for (int i = 0; i < evento.size(); i++)
	{
		if(evento[i].tipo == ABRE) bota(evento[i].id);
		else if(evento[i].tipo == FECHA) tira(evento[i].id);
		else consulta(evento[i].id);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	int x1, x2, y1, y2;
	int origem;
	cin >>  origem >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		//~ printf("%intd %intd %intd %intd\n", x1, y1, x2, y2);
		if(x1 < x2){
			seg.pb(segmento(pv(x1, y1), pv(x2, y2)));
		}else{
			seg.pb(segmento(pv(x2, y2), pv(x1, y1)));
		}
		evento.pb(event(seg[i].a, ABRE, i));
		evento.pb(event(seg[i].b, FECHA, i));
		
	}
	//~ cin >> x1;
	//~ printf("oi\n");
	evento.pb(event(pv(origem, 1000000000LL), CONSULTA, n));
	sweep();
	int ult = dfs(n);
	if(ult == n){
		cout << origem << "\n";
	}else{
		if(seg[ult].a.y < seg[ult].b.y) cout << seg[ult].a.x << "\n";
		else cout << seg[ult].b.x << "\n";
	}
	
	return 0;
}
