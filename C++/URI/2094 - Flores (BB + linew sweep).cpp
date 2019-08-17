#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef double ld;
#define F first
#define S second
#define pb push_back
#define ABRE 0
#define FECHA 1

ld PI = acos(-1);
ld eps = 1e-9;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
};

vector<pv> vet;
int n, k;

ld dist(pv a, pv b){
	return hypot(a.x - b.x, a.y - b.y);
}	

ld polarAngle(pv v){
	ld x = v.x;
	ld y = v.y;
	
	ld aux = atan2(y, x);
	
	if(aux < 0) aux += 2.0*PI;
	
	return aux;
}

ld toDegree(ld rad){
	return rad * 180 / PI;
}

pair<ld, ld> buildRange(pv A, pv B, ld r){
	ld d = dist(A, B);
	if(d > 2*r + eps) return {-1, -1};
	ld polar = polarAngle(B);
	//~ if(fabs(d - 2*r) < eps) return {polar, polar};
	
	ld ang = acos(d / (2 * r));//cuidado com raio 0
	
	ld entrada = polar - ang;
	ld saida = polar + ang;
	
	if(entrada < 0) entrada += 2*PI;
	if(saida > 360) saida -= 2*PI;
	return {entrada, saida};
}

void printa(pv a){
	cout << "(" << a.x << ", " << a.y << ")";
}

bool ok(ld r, int id){
	//~ vector<pair<ld, ld> > sl;
	vector<pair<ld, int> > eve;
	
	for (int i = 0; i < n; i++)
	{
		if(i == id) continue;
		pair<ld, ld> range = buildRange(vet[id] - vet[id], vet[i] - vet[id], r);
		if(range.F < 0) continue;
		
		//~ printa(vet[i] - vet[id]);
		//~ cout << ": " << toDegree(range.F) << " " << toDegree(range.S) << endl;
		if(range.F <= range.S){
			eve.pb({range.F, ABRE});
			eve.pb({range.S, FECHA});
		}else{
			eve.pb({range.F, ABRE});
			eve.pb({2*PI, FECHA});
			
			eve.pb({0, ABRE});
			eve.pb({range.S, FECHA});
		}
	}
	
	int atv = 0;
	sort(eve.begin(), eve.end());
	for (int i = 0; i < eve.size(); i++)
	{
		//~ cout << toDegree(eve[i].F) << " " << ((eve[i].S == ABRE) ? "ABRE" : "FECHA") << endl;
		if(eve[i].S == ABRE) atv++;
		else atv--;
		if(atv >= k - 1) return true;
	}
	return false;
}

ld solve(){
	//~ ok(0.8, 0);
	
	ld ans = 100000;
	for (int i = 0; i < vet.size(); i++)
	{
		ld lo = 0.0, hi = 100000, mid;
		for (int j = 0; j < 35; j++)
		{
			mid = (lo + hi) / 2;
			if(ok(mid, i)){
				hi = mid;
				ans = min(ans, mid);
			}else{
				lo = mid;
			}
		}
	}
	return ans;
}

int main(){
	//~ pair<ld, ld> p = buildRange(pv(0, 0), pv(1, 0), 0.49);
	//~ cout << toDegree(p.first) << " " << toDegree(p.second) << endl;
	
	int x, y;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &x, &y);
		vet.pb(pv(x, y));
	}
	
	if(k == 1){
		cout << "0.0000\n";
		return 0;
	}
	
	cout << fixed << setprecision(4) << solve() << "\n";	
	return 0;
}
