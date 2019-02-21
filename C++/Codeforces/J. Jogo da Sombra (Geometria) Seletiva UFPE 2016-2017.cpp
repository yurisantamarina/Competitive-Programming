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
};

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;	
}

double distanciaPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

int main () {
	int n;
	pv P;
	vector<pv> poligono;
	cin >> n;
	ll x, y;
	cin >> x >> y;
	P = pv(x, y);
	
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		poligono.pb(pv(x, y));
	}
	poligono.pb(poligono[0]);
	
	double total = 0;
	double ans = 0;
	for (int i = 0; i < poligono.size()-1; i++)
	{
		total += distanciaPt(poligono[i], poligono[i+1]);
		if(cross(poligono[i]-P, poligono[i+1]-P) > 0){
			ans += distanciaPt(poligono[i], poligono[i+1]);
		}
	}
	cout << fixed << setprecision(4) << ans*100.0/total << "\n";
	
	return 0;
}
