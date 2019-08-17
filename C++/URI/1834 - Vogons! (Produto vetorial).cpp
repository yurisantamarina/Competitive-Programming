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

int func(pv p1, pv p2, pv a){
	int c = cross(p2-p1, a-p1);
	if(c > 0) return 1;
	if(c < 0) return 2;
	return 0;
}

double dist(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

int main () {

	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	int x, y, x0, y0;
	cin >> x >> y >> x0 >> y0;
	
	pv p1(x, y), p2(x0, y0);
	
	int n;
	cin >> n;
	pv a;
	int cntOeste=0, habOeste=0;
	int cntLeste=0, habLeste=0;
	
	int h;
	int casu=0;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y >> h;
		a = pv(x, y);
		
		if(func(p1, p2, a)==1){
			cntOeste++;
			habOeste+=h;
		}else if(func(p1, p2, a)==2){
			cntLeste++;
			habLeste+=h;
		}else casu++;
	}
	
	printf("Relatorio Vogon #35987-2\n");
	printf("Distancia entre referencias: %.2lf anos-luz\n", dist(p1, p2));
	printf("Setor Oeste:\n");
	printf("- %d planeta(s)\n", cntOeste);
	printf("- %d bilhao(oes) de habitante(s)\n", habOeste);
	printf("Setor Leste:\n");
	printf("- %d planeta(s)\n", cntLeste);
	printf("- %d bilhao(oes) de habitante(s)\n", habLeste);
	printf("Casualidades: %d planeta(s)\n", casu);

	
	return 0;
}
