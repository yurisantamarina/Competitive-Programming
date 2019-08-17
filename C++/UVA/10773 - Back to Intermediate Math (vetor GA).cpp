#include <bits/stdc++.h>

using namespace std;

struct pv{
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
	double norma(){
		return hypot(x, y);
	}
};

int main(){
	int d, vu, vv, tc;
	cin >> tc;
	int caso = 1;
	while (tc--)
	{
		cin >> d >> vv >> vu;
		cout << "Case " << caso++ << ": ";
		if(vu == 0 || vv == 0){
			cout << "can't determine\n";
			continue;
		}
		if(vu <= vv){
			cout << "can't determine\n";
			continue;
		}
		
		pv v(vv, 0);
		pv u(0, vu);
		pv R(vv, vu);
		
		double k = (d * R.x) / R.y;
		double dist1 = sqrt(k * k + d * d);
		double t1 = dist1 / R.norma();
		
		pv u2(-v.x, sqrt(vu*vu - vv*vv));
		pv R2(0, u2.y);
		double dist2 = d;
		double t2 = dist2 / R2.norma();
		
		cout << fixed << setprecision(3) << fabs(t1 - t2) << "\n";
	}
	
	
	return 0;
}
