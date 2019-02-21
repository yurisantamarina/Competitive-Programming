#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef long double ld;
#define EPS 1e-20
#define PI acos(-1)

struct pv{
	double x, y;
	pv(){}
	pv(double _x, double _y){
		x = _x;
		y = _y;
	}
	
	
	
	pv operator + (pv other){
		return pv(x+other.x, y+other.y);
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	pv operator * (ld k){
		return pv(x*k, y*k);
	}
	
	pv operator / (int k){
		return pv(x/k, y/k);
	}
	
	
};

struct line{
	pv p0, v;
	line(){}
	line(pv _p0, pv _v){
		p0 = _p0;
		v = _v;
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

struct circle{
	pv centro;
	ld r;
	circle(){}
	circle(pv _centro, ld _r){
		centro = _centro;
		r = _r;
	}
};
//OKKKKKK
int cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

//OKKKKKK
int dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}

//OKKKKKKK
double distPt(pv a, pv b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}



bool colinear(pv a, pv b, pv c){
	return cross(b-a, c-b) == 0;
}


//retorna o ponto de interseccao de duas retas   OKKK
pv ptInterReta(line r, line s){
    pv v = r.v;
    pv u = s.v;
    
    pv p0 = r.p0;
    pv p1 = s.p0;
    
    long double t = (u.x * (p0.y - p1.y) + u.y * (p1.x - p0.x)) / cross(v, u);
    
    return pv(p0.x + (v.x * t), p0.y + (v.y * t));
}

//função que retorna a mediatriz
line getMediatriz(pv a, pv b){
	pv vet, medio, perp;
	medio = (a+b)/2.0;
	vet = b-a;
	perp = pv(-vet.y, vet.x);
	
	return line(medio, perp);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	vector<pv> v;
	int x, y, n;
	while (cin >> n, n)
	{
		v.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			v.pb(pv(x*2, y*2));
		}
		
		double d;
		pv centro;
		line m1, m2;
		int ans = n > 1 ? 2 : 1;
		int cnt;
		for (int i = 0; i < n; i++)
		{
			for (int j = i+1; j < n; j++)
			{
				for (int k = j+1; k < n; k++)
				{
					if(colinear(v[i], v[j], v[k])) continue;
					m1 = getMediatriz(v[i], v[j]);
					m2 = getMediatriz(v[i], v[k]);
					centro = ptInterReta(m1, m2);
					d = distPt(v[i], centro);
					cnt = 3;
					
					for (int l = 0; l < n; l++)
					{
						if(i==l || j==l || k==l) continue;
						if(distPt(v[l], centro) == d) cnt++;
					}
					ans = max(ans, cnt);
				}
				
			}
			
		}
		cout << ans << endl;
		
	}
	
	return 0;
}
