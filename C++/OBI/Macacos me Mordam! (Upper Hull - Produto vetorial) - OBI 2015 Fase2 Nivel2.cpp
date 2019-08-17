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
		return x < other.x;
	}
};

vector<pv> p(300010);

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

int main () {
	ll n, x, y;
	cin >> n;
	
	vector<pv> v;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		v.pb(pv(x, y));
	}
	sort(v.begin(), v.end());
	
	int sz=0;
	p[sz++] = v[0];
	//~ printf("Insere %lld, %lld\n", v[0].x, v[0].y);
	
	pv a, b, c;
	for (int i = 1; i < n; i++)
	{
		if(sz >= 2){
			a = p[sz-2];
			b = p[sz-1];
			c = v[i];
			
			while (sz>1 && cross(b-a, c-b) >= 0)
			{
				sz--;
				//~ printf("Remove %lld, %lld\n", p[sz].x, p[sz].y);
				a = p[sz-2];
				b = p[sz-1];
			}
			p[sz++] = c;
			//~ printf("Insere %lld, %lld\n", c.x, c.y);
		}else{
			p[sz++] = v[i];
			//~ printf("Insere %lld, %lld\n", v[i].x, v[i].y);
		}
	}
	
	
	cout << sz-1 << "\n";
	
	return 0;
}
