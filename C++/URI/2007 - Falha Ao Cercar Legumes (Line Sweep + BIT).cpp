#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
const ll MOD = 0;
const ll N = 0;

struct event{
	int x, y, tipo;
	int custo;
	event(){}
	event(int a, int b, int c){
		x = a;
		y = b;
		tipo = c;
	}
	event(int a, int b, int c, int d){
		x = a;
		y = b;
		tipo = c;
		custo = d;
	}
	
	bool operator < (event other) const {
		if(x==other.x) return tipo < other.tipo;
		return x < other.x;
	}
};

int abre = 2;
int fecha = 1;
int pt = 3;

vector<event> ponto;
vector<event> poligono;
vector<event> evento;
map<int, int> mapa;
int bit[201010];

void update(int pos, int val){
	while (pos < 201010)
	{
		bit[pos] += val;
		pos += pos & (-pos);
	}
}

int query(int pos){
	int ans = 0;
	while (pos > 0)
	{
		ans += bit[pos];
		pos -= pos & (-pos);
	}
	return ans;
}

int main () {

	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int qtdPonto, qtdVertices;
	int x, y;
	
	cin >> qtdPonto >> qtdVertices;
	
	set<int> s;
	for (int i = 0; i < qtdPonto; i++)
	{
		cin >> x >> y;
		s.insert(x);
		s.insert(y);
		//~ ponto.pb(event(x, y, -1));
		evento.pb(event(x, y, pt, i+1));
	}
	for (int i = 0; i < qtdVertices; i++)
	{
		cin >> x >> y;
		s.insert(x);
		s.insert(y);
		poligono.pb(event(x, y, -1));
	}
	
	poligono.pb(poligono[0]);
	for (int i = 0; i < poligono.size()-1; i++)
	{
		if(poligono[i].y == poligono[i+1].y){
			if(poligono[i].x < poligono[i+1].x){
				evento.pb(event(poligono[i].x, poligono[i].y, abre));
				evento.pb(event(poligono[i+1].x, poligono[i+1].y, fecha));
			}else{
				evento.pb(event(poligono[i].x, poligono[i].y, fecha));
				evento.pb(event(poligono[i+1].x, poligono[i+1].y, abre));
			}
		}
	}
	
	int idx = 1;
	//~ map<int, int> rev;
	for (auto i : s)
	{
		mapa[i] = idx++;
		//~ rev[idx-1] = i;
	}
	
	for (int i = 0; i < evento.size(); i++)
	{
		evento[i].x = mapa[evento[i].x];
		evento[i].y = mapa[evento[i].y];
	}
	sort(evento.begin(), evento.end());
	
	int qtd;
	ll ans = 0LL;
	
	for (int i = 0; i < evento.size(); i++)
	{
		if(evento[i].tipo == abre){
			update(evento[i].y, 1);
		}else if(evento[i].tipo == fecha){
			update(evento[i].y, -1);
		}else{
			//~ printf("Ponto %intd, %intd\n", rev[evento[i].x], rev[evento[i].y]);
			qtd = query(evento[i].y-1);
			if(qtd%2 == 0) ans += evento[i].custo;
		}
	}
	cout << ans << "\n";
	
	
	
	
	
	return 0;
}
