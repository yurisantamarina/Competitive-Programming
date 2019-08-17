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
#define EPS 1e-9
#define PI acos(-1)
#define ABRE 0
#define FECHA 1


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

struct pv{
	ld x, y;
	pv(){}
	pv(ld _x, ld _y){
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
	
	pv operator / (ld k){
		return pv(x/k, y/k);
	}
	
	bool operator == (pv other){
		return igual(x, other.x) && igual(y, other.y);
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

vector<circle> tree;

//OKKKKKK
ld dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}
//norma de um vetor  OKKKKKK
ld norma(pv a){
	return sqrtl(dot(a, a));
}

ld normasq(pv a){
	return dot(a, a);
}

struct event{
	int tipo, id, quad;
	ld ang;
	event(){}
	event(int _id, int _tipo, ld _ang, int _quad){
		tipo = _tipo;
		id = _id;
		ang = _ang;
		quad = _quad;
	}
	bool operator < (event other) const{
		if(quad == other.quad){
			if(igual(ang, other.ang)){
				if(tipo == other.tipo){
					if(tipo == ABRE){
						return menor(tree[id].centro.x*tree[id].centro.x + tree[id].centro.y*tree[id].centro.y - tree[id].r*tree[id].r, tree[other.id].centro.x*tree[other.id].centro.x + tree[other.id].centro.y*tree[other.id].centro.y - tree[other.id].r*tree[other.id].r);
					}
					return maior(tree[id].centro.x*tree[id].centro.x + tree[id].centro.y*tree[id].centro.y - tree[id].r*tree[id].r, tree[other.id].centro.x*tree[other.id].centro.x + tree[other.id].centro.y*tree[other.id].centro.y - tree[other.id].r*tree[other.id].r);
				}
				return tipo < other.tipo;
			}
			return menor(ang, other.ang);
		}
		return quad < other.quad;
	}
};

//radiano para grau   OKKKKKK
ld toDegree(ld rad){
	return rad * 180 / PI;
}

//OKKKKKK
ld cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}



//OKKKKKKK
ld distPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

//retorna a menor distancia entre um ponto e uma reta
ld distPtReta(pv pt, line r){
	
	return fabs(cross(r.v, pt - r.p0)) / norma(r.v);
	
}

//retorna a menor distancia de um ponto a um segmentl
ld distPtSeg(pv pt, seg r){
	if(maiorIgual(dot(pt - r.a, r.b - r.a), 0.0) && maiorIgual(dot(pt - r.b, r.a - r.b), 0.0)) return distPtReta(pt, line(r.a, r.b-r.a));
	
	//~ printf("oi\n");
	return min(distPt(pt, r.a), distPt(pt, r.b));
}

//angulo entre a reta horizontal com y = 0 e o vetor v      OKKKKKK
ld polarAngle(pv v){
	ld x = v.x;
	ld y = v.y;
	
	ld aux = atan2(y, x);
	
	if(menor(aux, 0.0)) aux += 2.0*PI;
	
	return aux;
}

ld polarAngle(ld aux){
	if(menor(aux, 0.0)) aux += 2.0*PI;
	if(maior(aux, 2.0*PI)) aux -= 2.0*PI;
	return aux;
}

void printaPonto(pv a){
	printf("(%.20Lf, %.20Lf)  ", a.x, a.y);
	
}

pair<ld, ld> interval(circle cc){
	ld x = cc.centro.x;
	ld y = cc.centro.y;
	ld r = cc.r;
	ld d = x*x + y*y;
	ld l = sqrtl(d - r*r);
	
	
	ld off = polarAngle(atan2(r, l));
	ld alpha = polarAngle(cc.centro);
	//~ cout << "alpha = " << toDegree(alpha) << endl;
	//~ cout << "off = " << toDegree(off) << endl;
	
	ld ini = polarAngle(alpha - off);
	ld fim = polarAngle(alpha + off);
	
	return mp(ini, fim);
}

vector<event> eve;

bool compare(int id1, int id2){
	//~ return menor(fabs(tree[id1].centro.x), fabs(tree[id2].centro.x));
	return menor(tree[id1].centro.x*tree[id1].centro.x + tree[id1].centro.y*tree[id1].centro.y - tree[id1].r*tree[id1].r, tree[id2].centro.x*tree[id2].centro.x + tree[id2].centro.y*tree[id2].centro.y - tree[id2].r*tree[id2].r);
	
	return menor(norma(tree[id1].centro), norma(tree[id2].centro));
}

set<int, bool(*)(int, int)> active(compare);
ld ans = 0.0;

void update(){
	if((int)active.size() == 0) return;
	//~ printf("Testando com ")
	ans = max(ans, norma(tree[*active.begin()].centro) - tree[*active.begin()].r); 
}

void printa(){
	cout << "active: ";
	for(auto i : active){
		printf("id = %d x = %.2Lf\n", i, tree[i].centro.x);
	}
	//~ cout << endl;
}

void sweep(){
	sort(eve.begin(), eve.end());
	//~ cout << "ABRE = " << ABRE << endl;
	//~ cout << "FECHA = " << FECHA << endl;
	for (int i = 0; i < (int)eve.size(); i++)
	{
		//~ printa();
		//~ printf("ang = %.20Lf  %.20Lf quad = %d ", toDegree(eve[i].ang), eve[i].ang, eve[i].quad);
		if(eve[i].tipo == ABRE){
			//~ printf("ABRINDO %d\n", eve[i].id);
			active.insert(eve[i].id);
		}else{
			//~ printf("FECHANDO %d\n", eve[i].id);
			active.erase(eve[i].id);
		}
		update();
		//~ cout << endl;
	}
	
}

int getQuad(ld ang){
	if(maiorIgual(ang, 0) && menorIgual(ang, PI/2.0)) return 1;
	if(maior(ang, PI/2.0) && menorIgual(ang, PI)) return 2;
	if(maior(ang, PI) && menorIgual(ang, 3.0*PI/2.0)) return 3;
	return 4;
}

int main(){
	//~ cout << fixed << setprecision(20) << endl;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	ld x, y, r;
	pair<ld, ld> range;
	ld in, outt;
	while (cin >> n, n)
	{
		tree.clear();
		eve.clear();
		ans = 0.0;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> r;
			tree.pb(circle(pv(x, y), r));
			range = interval(tree[i]);
			//~ cout << toDegree(range.F) << " " << toDegree(range.S) << "\n";
			in = range.F;
			outt = range.S;
			
			if(maior(in, outt)){
				eve.pb(event(i, ABRE, in, getQuad(in)));
				eve.pb(event(i, FECHA, 2*PI, 4));
				eve.pb(event(i, ABRE, 0.0, 1));
				eve.pb(event(i, FECHA, outt, getQuad(outt)));
				//~ printf("oi = ABRE %.5Lf- FECHA %.5Lf ABRE 0.0- FECHA %.5Lf\n", (in), ((ld)2.0*PI),  (outt));
				//~ printf("oi = %.5Lf-%.5Lf\n", toDegree(in), toDegree((ld)2.0*PI));
			}else{
				if(igual(in, 0.0)){
					eve.pb(event(i, ABRE, in, getQuad(in)));
					eve.pb(event(i, FECHA, outt, getQuad(outt)));
					//~ eve.pb(event(i, ABRE, 2*PI));
					//~ eve.pb(event(i, FECHA, 2*PI));
					//~ printf("oi2 = %.5Lf-%.5Lf %.5Lf-%.5Lf\n", toDegree(in), toDegree(outt), toDegree((ld)2.0*PI), toDegree((ld)2.0*PI));
					//~ printf("oi2 = %.5Lf-%.5Lf\n", (in), (outt));
				}else{
					//~ printf("OUT = %Lf\n", toDegree(outt));
					if(igual(outt, 2*PI)){
						eve.pb(event(i, ABRE, in, getQuad(in)));
						eve.pb(event(i, FECHA, outt, getQuad(outt)));
						//~ eve.pb(event(i, ABRE, 0.0));
						//~ eve.pb(event(i, FECHA, 0.0));
						//~ printf("oi3 = %.5Lf-%.5Lf 0-0\n", toDegree(in), toDegree(outt));
						//~ printf("oi3 = %.5Lf-%.5Lf\n", (in), (outt));
					}else{
						eve.pb(event(i, ABRE, in, getQuad(in)));
						eve.pb(event(i, FECHA, outt, getQuad(outt)));
						//~ printf("oi4 = %.5Lf-%.5Lf\n", toDegree(in), toDegree(outt));
						//~ printf("oi4 = %.5Lf-%.5Lf\n", (in), (outt));
					}
				}
			}
		}
		//~ cout << endl;
		sweep();
		cout << fixed << setprecision(3) << ans << endl;
	}
	
	return 0;
}
