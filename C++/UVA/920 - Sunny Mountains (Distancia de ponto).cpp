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
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	bool operator < (pv other) const{
		return x > other.x;
	}
};

vector<pv> ponto;

double dist(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

double solve(int idx, ll maior){
	double y = maior;
	
	pv a, b;
	a = ponto[idx];
	b = ponto[idx-1];
	
	pv u = a-b;
	double t = (y - b.y) / (u.y);
	double x = b.x + t * u.x;
	return dist(pv(x, y), a);
}

int main () {
	int tc, n;
	cin >> tc;
	ll x, y;
	while (tc--)
	{
		ponto.clear();
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			ponto.pb(pv(x, y));
		}
		sort(ponto.begin(), ponto.end());
		
		double ans = dist(ponto[0], ponto[1]);
		ll maior = ponto[1].y;
		for (int i = 2; i < ponto.size(); i++)
		{
			if(ponto[i].y > maior){
				ans += solve(i, maior);
				
				
				maior = ponto[i].y;
			}
		}
		cout << fixed << setprecision(2) << ans << endl;
	}
	
	
	return 0;
}
