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

int cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

int main () {
	
	int n;
	int d, a, b;
	cin >> n;
	
	if(n==0){
		cout << "Y\n";
		return 0;
	}
	
	vector<pv> cima, baixo;
	for (int i = 0; i < n; i++)
	{
		cin >> d >> a >> b;
		baixo.pb(pv(d, a));
		cima.pb(pv(d, b));
	}
	cin >> d >> a >> b;
	pv fimBaixo = pv(d, a);
	pv fimCima = pv(d, b);
	
	pv auxCima = cima[0];
	pv auxBaixo = baixo[0];
	pv origem = pv(0, 0);
	
	for (int i = 1; i < n; i++)
	{
		if(cross(auxBaixo-origem, baixo[i]-auxBaixo) > 0){
			auxBaixo = baixo[i];
		}
		
		if(cross(auxCima-origem, cima[i]-auxCima) < 0){
			auxCima = cima[i];
		}
	}
	
	if(cross(auxCima-origem, fimBaixo-auxCima)<=0 && cross(auxBaixo-origem, fimCima-auxBaixo)>=0) cout << "Y\n";
	else cout << "N\n";
	
	return 0;
}
