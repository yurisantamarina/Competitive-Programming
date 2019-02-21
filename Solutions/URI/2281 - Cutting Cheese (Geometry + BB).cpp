#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair
#define PI acos(-1)
typedef long long int ll;
typedef long double ld;
#define EPS 1e-9

struct pv{
	ld x, y, z;
	pv(){}
	pv(ld _x, ld _y, ld _z){
		x = _x;
		y = _y;
		z = _z;
	}
};

struct buraco{
	pv p;
	ld r;
	buraco(){}
	buraco(pv _p, ld _r){
		p = _p;
		r = _r;
	}
};

int qtdHoles, qtdCuts;
vector<buraco> hole;

ld volEsfera(buraco a){
	return (4.0/3.0) * PI * a.r * a.r * a.r; 
}

ld volSphericalCap(buraco a, ld h){
	ld aa = h * (2*a.r - h);
	return 1.0/6.0 * PI * h * (3*aa + h*h);
}

ld get(ld alt){
	ld vol = 100000.0*100000.0*alt;
	for (int i = 0; i < qtdHoles; i++)
	{
		if(hole[i].p.z + hole[i].r < alt) vol -= volEsfera(hole[i]);
		else if (hole[i].p.z - hole[i].r <= alt){
			vol -= volSphericalCap(hole[i], alt - (hole[i].p.z - hole[i].r));
		}
	}
	
	return vol;
}

int main(){
	ld x, y, z, r;
	cin >> qtdHoles >> qtdCuts;
	
	ld volTotal = 100000.0*100000.0*100000.0;
	for (int i = 0; i < qtdHoles; i++)
	{
		cin >> r >> x >> y >> z;
		hole.pb(buraco(pv(x*1.0, y*1.0, z*1.0), r*1.0));
		
		volTotal -= volEsfera(hole[i]);
		//~ cout << volEsfera(hole[i]) << endl;
	}
	//~ cout << endl;
	//~ cout << fixed << volTotal << endl;
	ld volCut = volTotal / qtdCuts;
	
	//~ cout << fixed << volCut << endl;
	//~ cout << endl;
	ld lo = 0, hi = 0;
	ld lstCut = 0.0;
	ld mid;
	
	for (int i = 0; i < qtdCuts; i++)
	{
		lo = lstCut;
		hi = 100000.0;
		
		for(int j = 0; j<100; j++){
			mid = (lo+hi)/2.0;
			
			ld aux = get(mid);
			if(volCut + EPS < aux - volCut * i){
				hi = mid;
			}else{
				lo = mid;
			}
		}
		
		cout << fixed << setprecision(9) << (lo+hi)/2000.0 - lstCut << endl;
		lstCut = (lo+hi)/2000.0;
	}
	
	
	return 0;
}
