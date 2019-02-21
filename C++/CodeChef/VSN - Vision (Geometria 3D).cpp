#include <bits/stdc++.h>

using namespace std;
#define pb push_back

struct pv{
	double x, y, z;
	pv(){}
	pv(double a, double b, double c){
		x = a;
		y = b;
		z = c;
	}
	
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y, z - other.z);
	}
	
	pv operator + (pv other) const{
		return pv(x + other.x, y + other.y, z + other.z);
	}
	
	pv operator * (double k) const{
		return pv(x * k, y * k, z * k);
	}
	
	pv operator ^ (pv other) const{
		return pv(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}
	
	double norma(){
		return sqrt(x * x + y * y + z * z);
	}
};

struct circle{
	pv centro;
	double r;
	circle(){}
	circle(pv a, double b){
		centro = a;
		r = b;
	}
};

struct line{
	pv p0, v;
	line(){}
	line(pv a, pv b){
		p0 = a;
		v = b;
	}
};

pv P, Q, d;
circle esfera;

double distPtReta(pv C, line s){
	pv U = s.v;
	pv V = C - s.p0;
	
	pv cross = U ^ V;
	
	return cross.norma() / U.norma();
}

bool ok(double t){
	pv Q2 = Q + (d * t);
	
	line s = line(P, Q2 - P);
	
	double dist = distPtReta(esfera.centro, s);
	//~ printf("dist = %lf\n", dist);
	return dist >= esfera.r;
}


int main(){
	int tc;
	scanf("%d", &tc);
	while (tc--)
	{
		scanf("%lf %lf %lf", &P.x, &P.y, &P.z);
		scanf("%lf %lf %lf", &Q.x, &Q.y, &Q.z);
		scanf("%lf %lf %lf", &d.x, &d.y, &d.z);
		scanf("%lf %lf %lf %lf", &esfera.centro.x, &esfera.centro.y, &esfera.centro.z, &esfera.r);
		
		double lo = 0, hi = 1000000000, mid, ans = 0;
		for (int i = 0; i < 100; i++)
		{
			mid = (lo + hi) / 2.0;
			if(ok(mid)){
				hi = mid;
				ans = mid;
			}else{
				lo = mid;
			}
		}
		//~ printf("ok(%d) = %d\n", 1, ok(1));
		
		printf("%.15lf\n", ans);
	}
	
	
	
	return 0;
}
