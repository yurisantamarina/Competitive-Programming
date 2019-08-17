#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define mp make_pair
#define F first
#define S second
#define pb push_back
#define eps 1e-9

struct pv{
	long double x, y;
	pv(){}
	pv(long double _x, long double _y){
		x = _x;
		y = _y;
	}
	
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
	
	bool operator < (pv other) const{//nao tem x igual
		return x < other.x;
	}
	
	bool operator == (pv other){
		return fabs(x - other.x) <= eps && fabs(y - other.y) <= eps;
	}
};

struct mon{
	pv a, b, c;
	mon(){}
	mon(pv _a, pv _b, pv _c){
		a = _a;
		b = _b;
		c = _c;
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};
vector<mon> montanha;
vector<seg> segmento;
vector<pv> ponto, poligono;

void reset(){
	montanha.clear();
	segmento.clear();
	ponto.clear();
	poligono.clear();
}

long double cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

int sinal(pv a, pv b, pv c){
	long double res = cross(b-a, c-b);
	if(res > eps) return 1;
	if(res < -eps) return -1;
	return 0;
}

bool inters(seg s, seg r){
	pv a = s.a;
	pv b = s.b;
	pv c = r.a;
	pv d = r.b;
	
	//~ if(colinear(a, b, c, d)) return false;
	
	int abc = sinal(a, b, c);
	int abd = sinal(a, b, d);
	int dca = sinal(d, c, a);
	int dcb = sinal(d, c, b);
	
	return abc!=abd && dca!=dcb;
}

long double area(){
	long double ans=0.0;
	for(int i=0; i<poligono.size()-1; i++){
		ans += cross(poligono[i], poligono[i+1]);
	}
	return fabs(ans)*0.5;
}


pv getPoint(seg r, seg s){
	pv p0 = r.a;
	pv p1 = s.a;
	pv u = r.b - r.a;
	pv v = s.b - s.a;
	
	long double tLinha = (u.x * (p1.y - p0.y) + u.y * (p0.x - p1.x)) / cross(v, u);
	pv ans = pv(p1.x + tLinha * v.x, p1.y + tLinha * v.y);
	
	return ans;
}

int n;

bool dentro(pv p){
	pv a, b, c;
	int s1, s2, s3;
	for (int i = 0; i < n; i++)
	{
		a = montanha[i].a;
		b = montanha[i].b;
		c = montanha[i].c;
		//~ if(colinear(a, b, ponto) || colinear(a, c, ponto) || colinear(b, c, ponto)) continue;
		s1 = sinal(p, a, b);
		s2 = sinal(p, b, c);
		s3 = sinal(p, c, a);
		if(s3 == 0) s3 = s2;
		if( s1==s2 && s2==s3){
			return true;
		}
	}
	return false;
}

void printaPonto(pv a){
	printf("(%.10lf, %.10lf)\n", a.x, a.y);
}

int main(){
	int l, r, h;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> n, n!=-1)
	{
		reset();
		
		int mn = 1000000000;
		int mx = -1000000000;
		for (int i = 0; i < n; i++)
		{
			cin >> l >> r >> h;
			montanha.pb(mon(pv(l, 0), pv(l + (r-l)/2.0, h), pv(r, 0)));
			segmento.pb(seg(montanha[i].a, montanha[i].b));
			segmento.pb(seg(montanha[i].b, montanha[i].c));
			segmento.pb(seg(montanha[i].a, montanha[i].c));
			
			//mn = min(mn, l);
			//mx = max(mx, r);
			
		}
		//~ segmento.pb(seg(pv(0, 0), pv(100010, 0)));
		
		for (int i = 0; i < segmento.size(); i++)
		{
			for (int j = i+1; j < segmento.size(); j++)
			{
				if(inters(segmento[i], segmento[j])){
					ponto.pb(getPoint(segmento[i], segmento[j]));
				}
			}
		}
		//ponto.pb(pv(mn, 0));
		//ponto.pb(pv(mx, 0));
		
		for (int i = 0; i < ponto.size(); i++)
		{
			//~ printaPonto(ponto[i]);
			if(!dentro(ponto[i])){
				poligono.pb(ponto[i]);
			}
			//~ else printaPonto(ponto[i]);
		}
		
		sort(poligono.begin(), poligono.end());
		poligono.pb(poligono[0]);
		//~ cout << endl << endl;
		//~ for (int i = 0; i < poligono.size(); i++)
		//~ {
			//~ printaPonto(poligono[i]);
		//~ }
		
		
		cout << fixed << setprecision(2) << area() << "\n";
	}
	
	
	return 0;
}
