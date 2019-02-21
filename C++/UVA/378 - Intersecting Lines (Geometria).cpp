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
		return pv(x - other.x, y - other.y);
	}
	
	pv operator * (double k){
		return pv(x+k, y+k);
	}
	
	pv operator + (pv other){
		return pv(x + other.x, y + other.y);
	}
};

struct reta{
	pv a, v;
	reta(){}
	reta(pv x, pv y){
		a = x;
		v = y;
	}
};

double cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

bool pertence(pv b, reta r){
	pv a = r.a;
	pv v = r.v;
	return cross(b-a, v) == 0;
}

bool paralelas(reta r, reta s){
	pv a = s.a;
	pv b = r.a;
	return cross(r.v, s.v)==0;
}

int inters(reta r, reta s, pv &a){
	pv p0 = r.a;
	pv p1 = s.a;
	pv u = r.v;
	pv v = s.v;
	
	if(paralelas(r, s)){
		//~ oioi;
		if(pertence(p0, s)){
			return 1;//iguais
		}
		return 0;//paralelas
	}
	
	double t = (v.x * (p1.y - p0.y) + v.y * (p0.x - p1.x)) / cross(v, u);
	//~ cout << "t = " << t << endl;
	
	a.x = p0.x + t*u.x;
	a.y = p0.y + t*u.y;
	return 2;//tem interseccao
}

int main () {
	int n;
	cin >> n;
	cout << fixed << setprecision(2);
	int a, b, c, d, e, f, g, h;
	
	cout << "INTERSECTING LINES OUTPUT\n";
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b >> c >> d >> e >> f >> g >> h;
		reta r = reta(pv(a, b), pv(c, d)-pv(a, b));
		reta s = reta(pv(e, f), pv(g, h)-pv(e, f));
		
		pv a;
		int ans = inters(r, s, a);
		if(ans==1) cout << "LINE\n";
		else if(ans==0) cout << "NONE\n";
		else cout << "POINT " << a.x << " " << a.y << "\n";
	}
	cout << "END OF OUTPUT\n";
	
	return 0;
}
