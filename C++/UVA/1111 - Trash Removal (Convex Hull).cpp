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
	ll x, y;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	bool operator < (pv other) const{
		if(x==other.x) return y < other.y;
		return x < other.x;
	}
};

vector<pv> ponto, poligono;
pv p1[10101];
pv p2[10101];
ll sz1;
ll sz2;
ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

bool ccw(pv a, pv b, pv c){
	return cross(b-a, c-b) > 0;
}

double norma(pv a){
	return sqrt(a.x*a.x + a.y*a.y);
}

double distPtReta(pv p, pv a, pv b){
	return fabs(cross(p-a, b-a))*1.0 / norma(b-a);
}

void convexHull(){
	poligono.clear();
	sort(ponto.begin(), ponto.end());
	sz1=0;
	sz2=0;
	for (ll i = 0; i < ponto.size(); i++)
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
	for (ll i = 0; i < sz1; i++)
	{
		poligono.pb(p1[i]);
	}
	for (ll i = sz2-2; i > 0; i--)
	{
		poligono.pb(p2[i]);
	}
	poligono.pb(poligono[0]);
	
	//~ for (ll i = 0; i < poligono.size(); i++)
	//~ {
		//~ cout << poligono[i].x << " " << poligono[i].y << endl;
	//~ }
	
	//~ for (int i = 0; i < sz1; i++)
	//~ {
		//~ cout << p1[i].x << " " << p1[i].y << endl;
	//~ }
	//~ cout << endl;
	//~ for (int i = 0; i < sz2; i++)
	//~ {
		//~ cout << p2[i].x << " " << p2[i].y << endl;
	//~ }
	//~ cout << endl;
	
	
}



int main () {
	ll n, x, y;
	ll caso = 1;
	while (cin >> n, n)
	{
		ponto.clear();
		for (ll i = 0; i < n; i++)
		{
			cin >> x >> y;
			ponto.pb(pv(x, y));
		}
		
		convexHull();
		double d, ans = 100000000000000.0;
		for (ll i = 0; i < poligono.size()-1; i++)
		{
			d = -1;
			for (ll j = 0; j < poligono.size()-1; j++)
			{
				//~ if(j==i || j==i+1) continue;
				d = max(d, distPtReta(poligono[j], poligono[i], poligono[i+1]));
			}
			if(d>=-0.5) ans = min(ans, d);
		}
		cout << "Case " << caso++ << ": " << fixed << setprecision(2) << ans << "\n";
		
	}
	
	
	
	return 0;
}
