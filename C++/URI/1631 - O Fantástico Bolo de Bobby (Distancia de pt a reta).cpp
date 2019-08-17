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

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
};

struct reta{
	pv p, v;
	reta(){}
	reta(pv a, pv b){
		p = a;
		v = b;
	}
};

vector<pv> ponto;

double norma(pv &v){
	return sqrt(v.x*v.x + v.y*v.y);
}

int cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

double dist(pv &c, reta &r){
	if(cross(r.v, c-r.p) == 0) return 0.0;
	
	return cross(r.v, c-r.p)*1.0 / norma(r.v);
}

double calc(int aa, int bb){
	pv a = ponto[aa];
	pv b = ponto[bb];
	
	double neg = 0;
	double posi = 0;
	double aux;
	
	reta r = reta(a, b-a);
	for (int i = 0; i < ponto.size(); i++)
	{
		if(i==aa || i==bb) continue;
		//~ printf("Distancia de (%d,%d) para reta (%d,%d)-(%d,%d)\n", ponto[i].x, ponto[i].y, a.x, a.y, b.x, b.y);
		aux = dist(ponto[i], r);
		//~ cout << "aux = " << aux << endl;
		if(aux < 0) neg-=aux;
		else posi+=aux;
	}
	
	//~ cout << posi << " " << neg << endl;
	return abs(posi - neg);
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int n, x, y;
	while (cin >> n, n)
	{
		ponto.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			ponto.pb(pv(x, y));
		}
		
		double ans = 1000000000000.0;
		for (int i = 0; i < n; i++)
		{
			for (int j = i+1; j < n; j++)
			{
				ans = min(ans, calc(i, j));
			}
		}
		cout << fixed << setprecision(3) << ans << "\n";
	}
	
	
	
	return 0;
}
