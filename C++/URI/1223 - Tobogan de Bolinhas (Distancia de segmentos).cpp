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

struct seg{
	pv a, b;
	seg(){}
	seg(pv aa, pv bb){
		a = aa;
		b = bb;
	}
};

vector<seg> aleta;
int L, H;

double distanciaPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

double cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

int dot(pv a, pv b){
	return a.x*b.x + a.y*b.y;
}

double norma(pv a){
	return sqrt(dot(a, a));
}

bool dentro(pv b, seg r){
	pv c, d;
	c = r.a;
	d = r.b;
	return dot(b-d, c-d) > 0 && dot(b-c, d-c) > 0;
}

double dist(seg r, seg s){
	pv a, b, c, d;
	a = r.a;
	b = r.b;
	c = s.a;
	d = s.b;
	
	if(dentro(b, s)){//significa que o ponto ta entre o segmento, pode pegar a distancia em linha reta até o segmento
		return fabs(cross(b-d, c-d))*1.0 / norma(c-d);
	}else{//ponto ta fora o segmento, pega a distancia dele pra um ponto da borda
		return distanciaPt(b, d);
	}
}

double solve(){
	double mn = 1000000000000.0;
	
	for (int i = 1; i < (int)aleta.size(); i++)
	{
		if(i%2==1){
			mn = min(mn, (double)L-aleta[i].b.x);
		}else{
			mn = min(mn, (double)aleta[i].b.x);
		}
		
		if(i < aleta.size()-1){
			mn = min(mn, dist(aleta[i], aleta[i+1]));//ve dist com a proxima
		}
	}
	
	return mn;
}

int main () {
	int xf, yf, yi;
	int n;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	while (cin >> n)
	{
		cin >> L >> H;
		aleta.clear();
		aleta.pb(seg());
		for (int i = 1; i <= n; i++)
		{
			cin >> yi >> xf >> yf;
			if(i%2!=0){
				aleta.pb(seg(pv(0, yi), pv(xf, yf)));
			}else{
				aleta.pb(seg(pv(L, yi), pv(xf, yf)));
			}
		}
		
		cout << fixed << setprecision(2) << solve() << "\n";
	}
	
	
	return 0;
}
