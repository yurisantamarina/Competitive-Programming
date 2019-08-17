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
	ld x, y;
	int id;
	pv(){}
	pv(ld _x, ld _y, int _id){
		x = _x;
		y = _y;
		id = _id;
	}
	
	pv operator + (pv other){
		return pv(x+other.x, y+other.y, id);
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y, id);
	}
	
	pv operator * (ld k){
		return pv(x*k, y*k, id);
	}
	
	pv operator / (ld k){
		return pv(x/k, y/k, id);
	}
};

bool igual(ld a, ld b){
	return fabs(a-b) < EPS;
}

bool maior(ld a, ld b){
	return a > EPS + b;
}

bool menor(ld a, ld b){
	return a + EPS < b;
}

bool maiorIgual(ld a, ld b){
	return maior(a, b) || igual(a, b);
}

bool menorIgual(ld a, ld b){
	return menor(a, b) || igual(a, b);
}


ld cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

ld dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}

ld norma(pv a){
	return sqrt(dot(a, a));
}

ld normasq(pv a){
	return (dot(a, a));
}

long double getAng(pv u){
	pv v = pv(1, 0, 0);
	long double ang = acos(dot(u, v)*1.0 / (norma(u)));
	if(u.y < 0){
		ang = 2*acos(-1) - ang;
	}
	return ang;
}

ld polarAngle(pv v){
	ld x = v.x;
	ld y = v.y;
	
	ld aux = atan2(y, x);
	
	if(menor(aux, 0.0)) aux += 2.0*PI;
	
	return aux;
}

ld angle2Vec(pv v, pv u){
	ld ang1 = polarAngle(v);
	ld ang2 = polarAngle(u);
	ld ans = 0.0;
	
	ans = min(fabs(ang1 - ang2), fabs(2.0*PI+ang1 - ang2));
	ans = min(ans, fabs(2.0*PI+ang2 - ang1));

	return ans;
}

bool ccw(pv a, pv b, pv c){
	ld aux = cross(b-a, c-b);
	
	return maior(aux, 0.0);
}

bool compare(pair<ld, pv> a, pair<ld, pv> b){
	if(menor(a.F, b.F)) return true;
	return false;
}

int main(){
	int n;
	cin >> n;
	ld x, y;
	vector<pair<ld, pv> > v;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		v.pb(mp(polarAngle(pv(x, y, i+1)), pv(x, y, i+1)));
	}
	
	sort(v.begin(), v.end(), compare);
	v.pb(v[0]);
	ld ans = 10000000000000.0;
	ld aux;
	int l, r;
	for (int i = 0; i < v.size()-1; i++)
	{
		aux = angle2Vec(v[i].S, v[i+1].S);
		if(menor(aux, ans)){
			ans = aux;
			l = v[i].S.id;
			r = v[i+1].S.id;
		}
	}
	cout << l << " " << r << "\n";
	
	
	
	return 0;
}
