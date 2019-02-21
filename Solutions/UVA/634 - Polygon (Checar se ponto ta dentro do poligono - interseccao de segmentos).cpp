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
		return pv(x - other.x, y - other.y);
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv x, pv y){
		a = x;
		b = y;
	}
};

vector<pv> poligono;
vector<seg> vertical;

void reset(){
	poligono.clear();
	vertical.clear();
}

int cross(pv a, pv b){
	ll c = a.x*b.y - a.y*b.x;
	if(c>0) return 1;
	if(c<0) return -1;
	return 0;
}

bool inters(seg r, seg s){
	pv a, b, c, d;
	a = r.a;
	b = r.b;
	
	c = s.a;
	d = s.b;
	
	//~ printf("(%lld, %lld) - (%lld, %lld) intersepta (%lld, %lld) - (%lld, %lld)\n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
	
	if(cross(b-a, d-a)!=cross(b-a, c-a) && cross(d-c, a-c)!=cross(d-c, b-c)) return true;
	
	
	//~ cout << "FALSE\n";
	return false;
}

int main () {
	ll n, x, y;
	while (cin >> n, n)
	{
		reset();
		for (ll i = 0; i < n; i++)
		{
			cin >> x >> y;
			poligono.pb(pv(x, y));
		}
		
		cin >> x >> y;
		pv p = pv(x, y);
		
		poligono.pb(poligono[0]);
		
		for (ll i = 0; i < poligono.size()-1; i++)
		{
			if(poligono[i].x == poligono[i+1].x){
				vertical.pb(seg(poligono[i], poligono[i+1]));
			}
		}
		
		seg newSeg = seg(p, pv(10000000000LL, p.y));
		
		int ans = 0;
		for (int i = 0; i < vertical.size(); i++)
		{
			if(newSeg.a.x >= vertical[i].a.x) continue;
			if(inters(newSeg, vertical[i])){
				
				//~ printf("(%lld, %lld) - (%lld, %lld) intersepta (%lld, %lld) - (%lld, %lld)\n", vertical[i].a.x, vertical[i].a.y, vertical[i].b.x, vertical[i].b.y, newSeg.a.x, newSeg.a.y, newSeg.b.x, newSeg.b.y);
				ans++;
			}
		}
		//~ cout << ans << endl;
		cout << ((ans%2==0) ? "F\n" : "T\n");
		
		
	}
	
	
	return 0;
}
