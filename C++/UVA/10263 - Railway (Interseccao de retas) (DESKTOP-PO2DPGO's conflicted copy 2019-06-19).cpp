#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;

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
};

int n;
vector<pv> ponto;

double cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

double dot(pv a, pv b){
	return a.x*b.x + a.y*b.y;
}

double norma(pv a){
	return sqrt(dot(a, a));
}

double dist(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

//~ pv inters(pv p0, pv u, pv p1, pv v){
	
	//~ double t = (v.x*(p1.y - p0.y) + v.y*(p0.x - p1.x))*1.0 / cross(v, u);
	//~ pv ans = pv(p0.x + t*u.x, p0.y + t*u.y);
	
	//~ return ans;
//~ }

pv inters(pv p0, pv v, pv p1, pv u){
	
	double t = (u.x*(p1.y - p0.y) + u.y*(p0.x - p1.x))*1.0 / cross(u, v);
	pv ans = pv(p0.x + t*v.x, p0.y + t*v.y);
	
	return ans;
}

double solve(int idx, pv &temp, pv M){
	pv a, b;
	a = ponto[idx];
	b = ponto[idx+1];
	pv u, v;
	u = b-a;
	if(dot(M-a, b-a) > 0 && dot(M-b, a-b) > 0){
		v = pv(u.y, -u.x);
		temp = inters(M, v, a, u);
		
		return fabs(cross(M-b, a-b)) / norma(b-a);
	}else{
		double d1, d2;
		d1 = dist(M, a);
		d2 = dist(M, b);
		if(d1 < d2){
			temp = a;
			return d1;
		}else{
			temp = b;
			return d2;
		}
	}
}

int main () {
	//se o ponto ta dentro do segmento, pega o vetor perpendicular ao segmento e calcula a interseccao das retas, senao pega algum ponto da ponta do segmento
	double x, y;
	pv M;
	while (cin >> x >> y)
	{
		//~ cin >> x >> y;
		M = pv(x, y);
		ponto.clear();
		cin >> n;
		for (int i = 0; i <= n; i++)
		{
			cin >> x >> y;
			ponto.pb(pv(x, y));
		}
		
		double ans = 10000000000000.0;
		pv P, temp;
		double aux;
		for (int i = 0; i < n; i++)
		{
			aux = solve(i, temp, M);
			//~ cout << "i = " << i << "  = " << aux << endl;
			if(aux < ans){
				ans = aux;
				P = temp;
			}
		}
		cout << fixed << setprecision(4) << P.x << "\n" << P.y << "\n";
	}
	
	
	
	
	return 0;
}
