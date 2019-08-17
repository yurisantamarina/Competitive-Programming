#include <bits/stdc++.h>



using namespace std;

#define eps 1e-9
#define pb push_back
#define MAXN 1010

double INF = 10000000.0;

struct pv{
	double x, y;
	pv(){}
	pv(double _x, double _y){
		x = _x;
		y = _y;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	pv operator + (pv other){
		return pv(x+other.x, y+other.y);
	}
	
	pv operator * (double k){
		return pv(x*k, y*k);
	}
};

struct line{
	pv p, v;
	line(){}
	line(pv _p, pv _v){
		p = _p;
		v = _v;
	}
};

double r;
vector<line> reta;


pv rotacionaHorario(pv p, double ang)
{
	ang=-ang;
	double rad = (ang * M_PI) / 180.0;
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

bool menor(double a, double b){
	return a+eps < b || fabs(a-b) < eps;
}

bool colisao(double d){
	return menor(d, r);
}

double getDist(int idx1, int idx2, double t){
	line r = reta[idx1];
	line s = reta[idx2];
	pv p0 = r.p;
	pv p1 = s.p;
	pv v = r.v;
	pv u = s.v;
	pv nwp0 = p0 + v * t;
	pv nwp1 = p1 + u * t;
	
	//~ printf("No tempo %.2lf")
	return hypot(nwp0.x - nwp1.x, nwp0.y - nwp1.y);
}

double solve(int idx1, int idx2){
	line r = reta[idx1];
	line s = reta[idx2];
	pv p0 = r.p;
	pv p1 = s.p;
	pv v = r.v;
	pv u = s.v;
	double d = getDist(idx1, idx2, 0.0);
	if(colisao(d)) return 0.0;
	
	double d1, d2;
	
	double ans = INF;
	double lo = 0.0, hi = INF, mid1, mid2;
	for (int i = 0; i < 53; i++)
	{
		mid1 = (2*lo + hi)/3.0;
		mid2 = (lo + 2*hi)/3.0;
		d1 = getDist(idx1, idx2, mid1);
		d2 = getDist(idx1, idx2, mid2);
		if(colisao(d1)){//testar d2 tbm
			ans = min(ans, mid1);
			hi = mid2;
		}else{
			if(menor(d1, d2)){
				hi = mid2;
			}else{
				lo = mid1;
			}
		}
	}
	return ans;
}

void printa(pv a){
	printf("(%.5lf %.5lf)\n", a.x, a.y);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	int tc;
	cin >> tc;
	while (tc--)
	{
		reta.clear();
		cin >> n >> r;
		double x, y, ang, speed;
		pv diretor;
		double ans = INF;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> ang >> speed;
			diretor = rotacionaHorario(pv(0, 1), ang) * speed;
			reta.pb(line(pv(x, y), diretor));
			//~ printa(diretor);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = i+1; j < n; j++)
			{
				ans = min(ans, solve(i, j));
			}
		}
		long long aux = round(ans);
		if(aux >= INF){
			cout << "No collision.\n";
		}else{
			cout << aux << "\n";
		}
		
	}
	
	
	
	
	
	
	return 0;
}
