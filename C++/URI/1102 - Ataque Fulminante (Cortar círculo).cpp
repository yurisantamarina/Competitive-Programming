#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define PI acos(-1)

struct pv{
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
	pv operator / (double k) const{
		return pv(x / k, y / k);
	}
	double operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	double operator * (pv other) const{
		return x * other.x + y * other.y;
	}
	double norma(){
		return sqrt((*this) * (*this));
	}
	pv operator + (pv other) const{
		return pv(x + other.x, y + other.y);
	}
	pv operator * (double k){
		return pv(x * k, y * k);
	}
};

struct circle{
	pv center;
	double r;
	circle(){}
	circle(pv a, double b){
		center = a;
		r = b;
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

int sinal( double a ){
	if(a > 0.0) return 1;
	if(a < 0.0) return -1;
	return 0;
}

double areaTriang(pv a, pv b, pv c){
	return fabs((b-a) ^ (c-a))/2.0;
}

double distPtReta(pv a, reta r){
	//~ printf("%.5lf / %.5lf\n", (a - r.p0) ^ (r.v), r.v.norma());
	//~ printf("a - p0 = (%.5lf, %.5lf) - (%.5lf, %.5lf) = (%.5lf, %.5lf)\n", a.x, a.y, r.p0.x, r.p0.y, a.x-r.p0.x, a.y-r.p0.y);
	//~ printf("r.v = (%.5lf, %.5lf)\n", r.v.x, r.v.y);
	return fabs((a - r.p0) ^ (r.v)) / r.v.norma();
}

double distPtPt(pv a, pv b){
	return (b-a).norma();
}

double distPtSeg(pv a, pv b, pv c){
	if(((a-b) * (c-b)) >= 0 && ((a-b) * (b-c)) >= 0) return distPtReta(a, reta(b, pv(c-b)));
	return min(distPtPt(a, b), distPtPt(a, c));
}

pair<double, double> getArea(reta r, circle c){
	double area1 = 0.0;
	double area2 = 0.0;
	
	//~ cout << endl;
	double areaCirc = PI * c.r * c.r;
	
	//~ r.v = r.v / r.v.norma();
	
	pv ct = c.center;
	double d = distPtReta(ct, r);
	double d2 = distPtSeg(ct, r.p0, r.p0 + r.v*1e9);
	//~ printf("centro(%.5lf, %.5lf)\n", ct.x, ct.y);
	//~ printf("d = %.5lf   d2 = %.5lf\n", d, d2);
	//~ return mp(0,0);
	if(d > c.r){
		//~ printf("oi\n");
		return mp(-10, -10);
	}
	
	double k = sqrt(c.r*c.r - d*d);
	//~ printf("d = %.5lf\nk = %.5lf\n", d, k);
	
	pv perp = pv(-r.v.y, r.v.x);
	perp = perp / perp.norma();
	
	pv pTmp1 = ct + perp * d;
	pv pTmp2 = ct - perp * d;
	//~ printf("(%.2lf, %.2lf)\n(%.2lf, %.2lf)\n\n", pTmp1.x, pTmp1.y, pTmp2.x, pTmp2.y);
	
	//~ printf("distPtReta(pTmp2, r) = %.2lf\n", distPtReta(pTmp2, r));
	if(distPtReta(pTmp2, r) < 1e-9) swap(pTmp1, pTmp2);
	//~ printf("(%.2lf, %.2lf)\n(%.2lf, %.2lf)\n\n", pTmp1.x, pTmp1.y, pTmp2.x, pTmp2.y);
	pv aux = r.p0 + r.v*1e9;
	if(!(((pTmp1 - r.p0) * (aux - r.p0)) >= 0 && ((pTmp1 - aux) * (r.p0 - aux)))){
		//~ printf("oi\n");
		return mp(-10, -10);
	}
	
	r.v = r.v / r.v.norma();
	pv p1 = pTmp1 + r.v * k;
	pv p2 = pTmp1 - r.v * k;
	//~ printf("interseccao:\n");
	//~ printf("  (%.2lf, %.2lf)\n  (%.2lf, %.2lf)\n\n", p1.x, p1.y, p2.x, p2.y);
	
	pv u = p1 - ct;
	pv v = p2 - ct;
	double ang = acos((u * v) / (u.norma() * v.norma()));
	
	
	double areaSetor = (ang * areaCirc) / (2.0*PI);
	
	area1 = areaSetor - areaTriang(ct, p1, p2);
	area2 = areaCirc - area1;
	
	if((r.v ^ (ct - r.p0)) >= 0.0) swap(area1, area2);
	
	return mp(area1, area2);
}

pv rotaciona(pv p, double ang)
{
	//~ printf("ang = %.5lf\n", ang);
	if(ang > 360) ang -= 360;
	if(ang < 0) ang = 360 + ang;
	//~ printf("ang = %.5lf\n", ang);
	double rad = (ang * PI) / 180.0;
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

bool inside(pv p, pv a, pv b, pv c){
int s1 = sinal((b-a)^(p-a));
int s2 = sinal((c-b)^(p-b));
int s3 = sinal((a-c)^(p-c));

return s1==s2 && s2==s3;
}

int main(){
	//~ pair<double, double> p = getArea(reta(pv(0,0), pv(1,100)), circle(pv(4,4), 4));
	//~ cout << fixed << setprecision(10) << p.first << " " << p.second << endl;
	ios_base::sync_with_stdio(0);cin.tie(0);
	double x, y, raio, A, Q;
	while(cin >> x >> y >> raio){
		if(x == 0 && y == 0 && raio == 0) break;
		circle circ = circle(pv(x, y), raio);
		
		cin >> x >> y;
		pv p0 = pv(x, y);
		cin >> A >> Q;
		
		pv dir;
		
		reta r1, r2;
		dir = rotaciona(pv(1, 0), A + Q / 2.0);
		//~ printf("dir(%.5lf, %.5lf)\n", dir.x, dir.y);
		
		r1 = reta(p0, dir);
		pair<double, double> p1 = getArea(r1, circ);
		
		
		dir = rotaciona(pv(1, 0), A - Q / 2.0);
		//~ printf("dir(%.5lf, %.5lf)\n", dir.x, dir.y);
		
		r2 = reta(p0, dir);
		pair<double, double> p2 = getArea(r2, circ);
		
		//~ printf("areaEsq = %.5lf  areaDir = %.5lf\n", p1.first, p1.second);
		//~ printf("areaEsq = %.5lf  areaDir = %.5lf\n", p2.first, p2.second);
		
		double ans;
		//~ printf("cross = %.5lf\n", (r1.v ^ r2.v));
		
		if(p1.first < 0 && p2.first < 0){
			pv aa = p0 + r1.v*1e9;
			pv bb = p0 + r2.v*1e9;
			if(inside(circ.center, aa, bb, p0)) cout << fixed << setprecision(1) << PI * raio * raio << "\n";
			else cout << "0.0\n";
			continue;
		}
		
		if(p1.first < 0){
			if((r1.v ^ r2.v) < 0) ans = p2.first;
			else ans = p2.second;
			cout << fixed << setprecision(1) << ans << "\n";
			continue;
		}
		
		if(p2.first < 0){
			if((r1.v ^ r2.v) < 0) ans = p1.second;
			else ans = p1.first;
			cout << fixed << setprecision(1) << ans << "\n";
			continue;
		}
		
		if((r1.v ^ r2.v) > 0) ans = p1.first - p2.first;
		else ans = p1.second - p2.second;
		
		//~ printf("%.5lf\n", ans);
		cout << fixed << setprecision(1) << ans << "\n";
		//~ cout << fixed << setprecision(1) << max(ans, 0.0) << "\n";
	}
	return 0;
}
