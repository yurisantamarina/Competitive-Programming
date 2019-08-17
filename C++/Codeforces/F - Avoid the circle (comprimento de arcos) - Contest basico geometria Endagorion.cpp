//~ http://codeforces.com/group/3qadGzUdR4/contest/101706/problem/F

#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define EPS 1e-9
#define F first
#define S second
#define PI acos(-1)

struct pv{
	long double x, y;
	pv(){}
	pv(long double a, long double b){
		x = a;
		y = b;
	}
	long double operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	long double operator * (pv other) const{
		return x * other.x + y * other.y;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
	pv operator + (pv other) const{
		return pv(x + other.x, y + other.y);
	}
	pv operator / (long double k) const{
		return pv(x / k, y / k);
	}
	pv operator * (long double k) const{
		return pv(x * k, y * k);
	}
	long double norma(){
		return sqrt((*this) * (*this));
	}
};

struct circle{
	pv c;
	long double r;
	circle(){}
	circle(pv a, long double b){
		c = a;
		r = b;
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

struct reta{
	pv p0, v;
	reta(){}
	reta(pv a, pv b){
		p0 = a;
		v = b;
	}
};

long double distPtPt(pv a, pv b){
	return (b-a).norma();
}


long double distPtReta(pv p, reta r){
	pv u = p - r.p0;
	long double area = fabs(r.v ^ u);
	
	return area / r.v.norma();
}

long double distPtSeg(pv p, seg s){
	pv a = s.a;
	pv b = s.b;
	if( ((p-a)*(b-a)) > EPS && ((p-b)*(a-b)) > EPS ) return distPtReta(p, reta(a, b-a));
	return min(distPtPt(p, a), distPtPt(p, b));
}

pv rHR(pv p, long double rad)
{
	rad=-rad;
	//~ long double rad = (ang * M_PI) / 180.0;
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

pv rAHR(pv p, long double rad)
{
	//~ long double rad = (ang * M_PI) / 180.0;
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}


bool onBorder(pv p, circle circ){
	//~ printf("dist = %.5lf\n", distPtPt(p, circ.c));
	return fabs(distPtPt(p, circ.c) - circ.r) < EPS;
}

long double getAngle(long double r, long double d, long double k){
	long double num = d*d + k*k - r*r;
	long double den = 2*d*k;
	
	return acos(num / den);
}

pair<pv, pv> get(pv p, circle circ){
	if(onBorder(p, circ)) return mp(p, p);
	long double r = circ.r;
	pv center = circ.c;
	
	//~ printf("p(%.2lf, %.2lf)\n", p.x, p.y);
	//~ printf("center(%.2lf, %.2lf)\n", center.x, center.y);
	long double d = distPtPt(p, center);
	long double k = sqrt(d * d - r * r);
	
	//~ cout << "d = " << d << "  k = " << k << endl;
	long double ang = getAngle(r, d, k);
	
	pv dc = rAHR(center - p, ang);
	dc = dc / dc.norma();
	pv p2 = p + dc * k;
	
	dc = rHR(center - p, ang);
	dc = dc / dc.norma();
	pv p1 = p + dc * k;
	
	return mp(p1, p2);
}

long double getArc(circle circ, pv a, pv b){
	pv center = circ.c;
	
	pv v = a - center;
	pv u = b - center;
	
	long double arcTotal = 2.0 * PI * circ.r;
	long double ang = acos((v * u) / (v.norma() * u.norma()));
	
	return ((ang * arcTotal)/(2*PI));
}

int main(){
	long double x, y, r;
	
	cin >> x >> y;
	pv A(x, y);
	cin >> x >> y;
	pv B(x, y);
	
	cin >> x >> y >> r;
	circle circ(pv(x, y), r);
	
	if(distPtSeg(circ.c, seg(A, B)) >= circ.r){
		cout << fixed << setprecision(6) << distPtPt(A, B) << "\n";
		return 0;
	}
	
	pair<pv, pv> a = get(A, circ);
	pair<pv, pv> b = get(B, circ);
	
	
	long double ans = min(getArc(circ, a.F, b.S) + distPtPt(A, a.F) + distPtPt(b.S, B), getArc(circ, a.S, b.F) + distPtPt(A, a.S) + distPtPt(b.F, B));
	cout << fixed << setprecision(6) << ans << "\n";
	
	return 0;
}
