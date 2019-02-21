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
	
	bool operator < (pv other){ // CONST
		if(x == other.x) return y < other.y;
		return x < other.x;
	}
};

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

bool ccw(pv a, pv b, pv c){
	return cross(b-a, c-b) > 0;
}

pv pilha1[100000];
pv pilha2[100000];
vector<pv> ponto;
ll sz1, sz2;

double dist(pv a, pv b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double build(){
	double ans = 0;
	sz1 = 0;
	sz2 = 0;
	
	for (ll i = 0; i < ponto.size(); i++)
	{
		while (sz1 > 1 && ccw(pilha1[sz1-2], pilha1[sz1-1], ponto[i]))
		{
			sz1--;
		}
		pilha1[sz1++] = ponto[i];
		
		while (sz2 > 1 && !ccw(pilha2[sz2-2], pilha2[sz2-1], ponto[i]))
		{
			sz2--;
		}
		pilha2[sz2++] = ponto[i];
	}
	
	//~ cout << sz1 << " " << sz2 << endl;
	
	for (ll i = 0; i < sz1 - 1; i++){
		ans += dist(pilha1[i], pilha1[i+1]);
	}
	
	for (ll i = 0; i < sz2 - 1; i++){
		ans += dist(pilha2[i], pilha2[i+1]);
	}
	return ans;
}

int main () {
	ll t, x, y, n, lixo;
	cin >> t;
	while (t--)
	{
		ponto.clear();
		cin >> lixo >> n;
		for (ll i = 0; i < n; i++)
		{
			cin >> x >> y;
			ponto.pb(pv(x, y));
		}
		sort(ponto.begin(), ponto.end());
		//~ for (ll i = 0; i < ponto.size(); i++)
		//~ {
			//~ cout << ponto[i].x << " " << ponto[i].y << endl;;
		//~ }
		
		
		cout << fixed << setprecision(5) << max(build(), double(lixo)) << "\n";
		
	}
	
	
	
	return 0;
}
