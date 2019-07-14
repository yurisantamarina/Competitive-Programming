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

#define PI acos(-1)
#define EPS 1e-5

struct pv{
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	pv operator + (pv other){
		return pv(x+other.x, y+other.y);
	}
	
	bool operator < (pv other) const {
		if(fabs(x-other.x) < EPS) return y+EPS < other.y;
		return x+EPS < other.x;
	}
};

pv rotaciona(pv p, double rad)
{
	rad=-rad;
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

vector<pv> ponto;
pv centro, aux;
pv p1[101010];
pv p2[101010];
int sz1, sz2;

double cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

bool ccw(pv a, pv b, pv c){
	return cross(b-a, c-a) > 0.0;
}

double convexHull(){
	sort(ponto.begin(), ponto.end());
	double area = 0.0;
	vector<pv> poligono;
	sz1 = 0;
	sz2 = 0;
	
	for (int i = 0; i < ponto.size(); i++)
	{
		while (sz1 > 1 && ccw(p1[sz1-2], p1[sz1-1], ponto[i]))
			sz1--;
		p1[sz1++] = ponto[i];
		
		while (sz2 > 1 && !ccw(p2[sz2-2], p2[sz2-1], ponto[i]))
			sz2--;
		p2[sz2++] = ponto[i];
	}
	
	
	for (int i = 0; i < sz1; i++)
	{
		poligono.pb(p1[i]);
	}
	for (int i = sz2-2; i > 0; i--)
	{
		poligono.pb(p2[i]);
	}
	
	for (int i = 1; i < poligono.size()-1; i++)
	{
		area += fabs(cross(poligono[i+1]-poligono[0], poligono[i]-poligono[0]));
	}
	
	return area*0.5;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int tc, n;
	double x, y, w, h, ang;
	cin >> tc;
	double PI = acos(-1);
	while (tc--)
	{
		ponto.clear();
		cin >> n;
		
		double areaBoard = 0.0;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> w >> h >> ang;
			areaBoard += w*h;
			centro = pv(x, y);
			ang = (ang * PI) / 180.0;
			
			//ROTACIONA OS 4 PONTOS DO RETANGULO EM RELACAO AO CENTRO
			aux = rotaciona(pv(w*0.5, h*0.5), ang);
			ponto.pb(aux+centro);
			aux = rotaciona(pv(-w*0.5, h*0.5), ang);
			ponto.pb(aux+centro);
			aux = rotaciona(pv(w*0.5, -h*0.5), ang);
			ponto.pb(aux+centro);
			aux = rotaciona(pv(-w*0.5, -h*0.5), ang);
			ponto.pb(aux+centro);
		}

		cout << fixed << setprecision(1) << areaBoard*100.0 / convexHull() << " %\n";
	}
	
	
	
	return 0;
}
