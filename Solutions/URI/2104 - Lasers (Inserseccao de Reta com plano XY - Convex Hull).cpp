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
	double x, y, z;
	pv(){}
	pv(double a, double b, double c){
		x = a;
		y = b;
		z = c;
	}
	pv(double a, double b){
		x = a;
		y = b;
		z = 0.0;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y, z-other.z);
	}
	
	bool operator < (pv other) const{
		if(x == other.x) return y < other.y;
		return x < other.x;
	}
};

double cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

pv base;
pv plat;
vector<pv> ponto;
vector<pv> poligono;
int n;
pv p1[10000];
pv p2[10000];
int sz1, sz2;

pv getPonto(){
	pv u = plat - base;
	double t = -base.z / u.z;
	double x, y;
	x = base.x + t*u.x;
	y = base.y + t*u.y;
	
	return pv(x, y);
}

bool ccw(pv a, pv b, pv c){
	return cross(b-a, c-a) > 0;
}

double getArea(){
	poligono.clear();
	double area = 0.0;
	
	sz1 = 0;
	sz2 = 0;
	sort(ponto.begin(), ponto.end());
	
	for (int i = 0; i < (int)ponto.size(); i++)
	{
		while (sz1 > 1 && ccw(p1[sz1-2], p1[sz1-1], ponto[i]))
		{
			sz1--;
		}
		p1[sz1++] = ponto[i];
		
		while (sz2 > 1 && !ccw(p2[sz2-2], p2[sz2-1], ponto[i]))
		{
			sz2--;
		}
		p2[sz2++] = ponto[i];
	}
	
	for (int i = 0; i < sz1; i++)
	{
		poligono.pb(p1[i]);
	}
	for (int i = sz2-2; i >= 1; i--)
	{
		poligono.pb(p2[i]);
	}
	
	for (int i = 1; i < (int)poligono.size()-1; i++)
	{
		area += fabs(cross(poligono[i]-poligono[0], poligono[i+1]-poligono[0]));
	}
	
	return area*0.5;
}

int main () {
	double x, y, z;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	while (cin >> n, n)
	{
		ponto.clear();
		cin >> x >> y >> z;
		base = pv(x, y, z);
		
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> z;
			plat = pv(x, y, z);
			ponto.pb(getPonto());
		}
		
		cout << fixed << setprecision(2) << getArea() << "\n";
	}
	
	return 0;
}
