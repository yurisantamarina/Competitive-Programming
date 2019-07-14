#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 1000010
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;

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
	
	pv operator + (pv other){
		return pv(x + other.x, y + other.y);
	}
	
	pv operator / (double k){
		return pv(x / k, y / k);
	}
	
	pv operator * (double k){
		return pv(x * k, y * k);
	}
	
	double operator * (pv other){
		return x * other.x + y * other.y;
	}
	
	double operator ^ (pv other){
		return x * other.y - y * other.x;
	}
	
	double norma(){
		return sqrt((*this) * (*this));
	}
	
	pv unit(){
		return pv(x / norma(), y / norma());
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

pv A1, A2, B1, B2;

pv inter(line r, line s){
	pv p0 = r.p0, v = r.v;
	pv p1 = s.p0, u = s.v;
	
	double t_ = (v.x * (p1.y - p0.y) + v.y * (p0.x - p1.x)) / (u ^ v);
	
	return (p1 + (u * t_));
}

pv solve(){
	pv MA = (A1 + A2) / 2.0;
	pv vetA = A1 - A2;
	pv vetPerpA = pv(-vetA.y, vetA.x);
	line rA = line(MA, vetPerpA);
	
	pv MB = (B1 + B2) / 2.0;
	pv vetB = B1 - B2;
	pv vetPerpB = pv(-vetB.y, vetB.x);
	line rB = line(MB, vetPerpB);
	
	//~ return pv(0, 0);
	return inter(rA, rB);
}

int main(){
	int tc, caso = 1;
	double x, y;
	scanf("%d", &tc);
	while (tc--)
	{
		scanf("%lf %lf", &x, &y);
		A1 = pv(x, y);
		scanf("%lf %lf", &x, &y);
		B1 = pv(x, y);
		scanf("%lf %lf", &x, &y);
		A2 = pv(x, y);
		scanf("%lf %lf", &x, &y);
		B2 = pv(x, y);
		
		pv ans = solve();
		printf("Caso #%d: %.2lf %.2lf\n", caso++, ans.x, ans.y);
	}
	
	
	return 0;
}
