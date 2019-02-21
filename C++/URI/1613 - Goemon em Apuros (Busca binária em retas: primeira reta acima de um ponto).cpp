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

struct line{
	pv p0, v;
	bool abre;
	line(){}
	line(pv a, pv b, bool c){
		p0 = a;
		v = b;
		abre = c;
	}
	
	bool operator < (line other) const{
		return p0.y < other.p0.y;
	}
};

int cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

vector<line> reta;
pv origem;

bool ok(pv p){
	pv a = origem, b;
	int lo = 0;
	int hi = (int)reta.size()-1;
	int mid;
	int acima = -1;
	
	int c;
	for (int i = 0; i < 15; i++)
	{
		mid = (lo+hi)/2;
		b = reta[mid].p0;
		
		c = cross(b-a, p-b);
		if(c == 0) return false;
		if(c > 0){
			lo = mid+1;
		}else{
			hi = mid-1;
			acima = mid;
		}
	}
	
	if(acima == -1) return false;
	if(reta[acima].abre == false) return true;
	return false;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int x, y;
	int tc, p, ini, fim;
	cin >> tc;
	
	while (tc--)
	{
		cin >> x >> y;
		origem = pv(x, y);
		cin >> p;
		reta.clear();
		for (int i = 0; i < p; i++)
		{
			cin >> ini >> fim;
			reta.pb(line(pv(0, ini), pv(0, ini)-origem, true));
			reta.pb(line(pv(0, fim), pv(0, fim)-origem, false));
		}
		sort(reta.begin(), reta.end());
		
		
		cin >> p;
		int ans = 0LL;
		for (int i = 0; i < p; i++)
		{
			cin >> x >> y;
			if(ok(pv(x, y))) ans++;
		}
		cout << ans << "\n";
		
	}
	
	
	return 0;
}
