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

#define EPS 1e-10
#define PI acos(-1)

struct pv{
	ll x, y, h;
	double ang;
	double dist;
	pv(){}
	pv(ll a, ll b, ll c, double d, double e){
		x = a;
		y = b;
		h = c;
		ang = d;
		dist = e;
	}
	
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
	
	bool operator < (pv other) const{
		if(fabs(ang - other.ang) < EPS) return dist < other.dist;
		return ang < other.ang;
	}
	//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
};

vector<pv> ponto;

ll dot(pv a, pv b){
	return a.x*b.x + a.y*b.y;
}

double norma(pv a){
	return sqrt(dot(a, a));
}

double dist(ll x, ll y, ll x0, ll y0){
	return hypot(x-x0, y-y0);
}

bool compare(pv a, pv b){
	if(a.x==b.x) return a.y < b.y;
	return a.x < b.x;
}

double getAngulo(pv a){
	double ang = dot(a, pv(1, 0))*1.0 / (norma(a) * norma(pv(1, 0)));
	
	
	ang = acos(ang);
	if(a.y < 0){
		ang = 2*PI - ang;
	}
	
	return ang;
}


//função pra ordenar em relação ao angulo polar só com cross OKKKKKK
bool comparePolarAngle(pv a, pv b){
	if(a == b){
		return true;//pontos iguais
	}
	pv origem = pv(0, 0);
	if(a == origem){
		return true;
	}
	if(b == origem){
		return false;
	}
	
	if(igual(a.y, 0.0) && igual(b.y, 0.0)){//ambos no eixo x
		if(menor(a.x, 0.0) && maior(b.x, 0.0)){
			return false;
		}
		if(maior(a.x, 0.0) && menor(b.x, 0.0)){
			return true;
		}
		
		//lados opostos
		if(menor(distPt(origem, a), distPt(origem, b))){
			return true;
		}
		return false;
	}
	if(igual(a.y, 0.0)){
		if(maior(a.x, 0.0)){//pra direita
			return true;
		}else{//pra esquerda
			if(maior(b.y, 0.0)){
				return false;
			}
			return true;
		}
	}
	
	if(igual(b.y, 0.0)){
		if(maior(b.x, 0.0)){
			return false;
		}else{
			if(maior(a.y, 0.0)){
				return true;
			}
			return false;
		}
	}
	//nesse momento nenhum está com y == 0
	if(maior(a.y, 0.0) && menor(b.y, 0.0)){
		return true;
	}
	if(menor(a.y, 0.0) && maior(b.y, 0.0)){
		return false;
	}
	
	if(colinear(origem, a, b)){
		if(menor(distPt(origem, a), distPt(origem, b))){
			return true;
		}
		return false;
	}
		
	if(maior(cross(b-origem, a-origem), 0.0)){
		return false;
	}
	return true;
}


int main () {
	ll x, y, h;
	int n;
	int caso = 1;
	while (cin >> n, n)
	{
		ponto.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> h;
			ponto.pb(pv(x, y, h, getAngulo(pv(x, y)), dist(x, y, 0, 0)));
		}
		sort(ponto.begin(), ponto.end(), comparePolarAngle);
		
		vector<pv> saida;
		ll maior;
		for (int i = 0; i < ponto.size(); i++)
		{
			if(i==0 || fabs(ponto[i].ang - ponto[i-1].ang) > EPS){
				maior = ponto[i].h;
			}else{
				if(ponto[i].h <= maior){
					saida.pb(ponto[i]);
				}else maior = ponto[i].h;
				
			}
		}
		
		cout << "Data set " << caso++ << ":\n";
		
		if(saida.size() == 0){
			cout << "All the lights are visible.\n";
		}else{
			cout << "Some lights are not visible:\n";
			sort(saida.begin(), saida.end(), compare);
			for (int i = 0; i < saida.size(); i++)
			{
				cout << "x = " << saida[i].x << ", y = " << saida[i].y;
				if(i==saida.size()-1) cout << ".\n";
				else cout << ";\n";
			}
		}
		
		
		
		
		
	}
	
	
	
	
	
	
	return 0;
}
