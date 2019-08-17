#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MISTO 0
#define ESQ_CENTRO 1
#define DIR_CENTRO 2
#define ESQ 3
#define DIR 4
typedef long long int ll;
long double INF = 10000000000000000000000.0;
#define PI acos(-1)
long double eps = 1e-9;

string TIPOS[] = {"MISTO", "ESQ_CENTRO", "DIR_CENTRO", "ESQ", "DIR"};

struct pv{
	long double x, y;
	pv(){}
	pv(long double _x, long double _y){
		x = _x;
		y = _y;
	}
	pv operator + (pv other){
		return pv(x+other.x, y+other.y);
	}
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	pv operator * (long double k){
		return pv(x*k, y*k);
	}
	
	bool operator < (pv other) const{
		if(fabs(x - other.x) < eps) return y+eps < other.y;
		return x+eps < other.x;
	}
	
	bool operator == (pv other){
		return fabs(x-other.x) < eps && fabs(y-other.y) < eps;
	}
};

struct segmento{
	pv a, b;
	segmento(){}
	segmento(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};

vector<pv> asteroid1, asteroid2, copiaAsteroid2, poligono;
vector<segmento> seg1, seg2;
pv vel1, vel2, vel;
long double NORMA_VEL;

ll crossInt(pv a, pv b){
	return (ll)a.x * (ll)b.y - (ll)a.y * (ll)b.x;
}

long double crossDouble(pv a, pv b){
	return (long double)a.x * (long double)b.y - (long double)a.y * (long double)b.x;
}

ll dotInt(pv a, pv b){
	return (ll)a.x * (ll)b.x + (ll)a.y * (ll)b.y;
}

long double dotDouble(pv a, pv b){
	return (long double)a.x * (long double)b.x + (long double)a.y * (long double)b.y;
}

long double norma(pv a){
	return sqrt(dotDouble(a, a));
}

long double getDistPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}
void printaPonto(pv a){
	printf("(%.2Lf, %.2Lf)\n", a.x, a.y);
}

int getTipoVertice(int idx){
	pv a = asteroid2[idx];
	int qtdEsq = 0, qtdDir = 0, qtdCentro = 0;
	int aux;
	pv v;
	
	for (int i = 0; i < (int)asteroid1.size(); i++)
	{
		v = asteroid1[i] - a;
		aux = crossInt(vel, v);
		if(aux > 0) qtdEsq++;
		else if(aux < 0) qtdDir++;
		else qtdCentro++;
	}
	//~ printf("vel = "); printaPonto(vel);
	//~ printf("ponto = "); printaPonto(a);
	//~ printf("qtdEsq = %d qtdDir = %d qtdCentro = %d\n\n", qtdEsq, qtdDir, qtdCentro);
	if(qtdEsq > 0 && qtdDir > 0) return MISTO;
	if(qtdEsq > 0 && qtdCentro > 0) return ESQ_CENTRO;
	if(qtdDir > 0 && qtdCentro > 0) return DIR_CENTRO;
	if(qtdEsq > 0) return ESQ;
	if(qtdDir > 0) return DIR;
}


void printaTipo(int tipo){
	printf("%s\n", TIPOS[tipo].c_str());
}

int sinalDouble(long double c){
	if(c > eps) return 1;
	if(c < -eps) return -1;
	return 0;
}

int sinal(ll c){
	if(c > 0) return 1;
	if(c < 0) return -1;
	return 0;
}

bool temInterseccaoSegInt(segmento r, segmento s){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	
	return sinal(crossInt(b-a, c-a))!=sinal(crossInt(b-a, d-a)) && sinal(crossInt(d-c, a-c))!=sinal(crossInt(d-c, b-c));
}

bool temInterseccaoSegDouble(segmento r, segmento s){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	
	return sinalDouble(crossDouble(b-a, c-a))!=sinalDouble(crossDouble(b-a, d-a)) && sinalDouble(crossDouble(d-c, a-c))!=sinalDouble(crossDouble(d-c, b-c));
}

vector<long double> tempos;

pv getPontoInterseccaoSeg(segmento r, segmento s){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	
	pv v = b-a;
	pv u = d-c;
	
	pv p0 = a;
	pv p1 = c;
	
	long double t = (u.x * (p0.y - p1.y) + u.y * (p1.x - p0.x)) / crossInt(v, u);
	
	return pv(p0.x + (v.x * t), p0.y + (v.y * t));
}

bool paralelos(segmento r, segmento s){//CUIDADO
	pv v1 = r.b - r.a;
	pv v2 = s.b - s.a;
	
	return fabs(crossDouble(v1, v2)) < eps;
}

bool taNoSegmento(pv p, segmento s){
	pv a = s.a;
	pv b = s.b;
	
	bool aux = dotDouble(p-a, b-a) > eps || fabs(dotDouble(p-a, b-a)) < eps;
	aux = aux && (dotDouble(p-b, a-b) > eps || fabs(dotDouble(p-b, a-b)) < eps);
	aux = aux && fabs(crossDouble(p-a, b-p)) < eps;
	
	//~ if(dotDouble(p-a, b-a) >= 0 && dotDouble(p-b, a-b) >= 0 && crossDouble(p-a, b-p)==0) return true;
	//~ return false;
	return aux;
}

pair<long double, long double> getTempo(pv a){
	//~ pv a = asteroid2[idx];
	segmento segAt(a, a + vel*100000);//CUIDADO
	pv pt;
	long double dist, tempo;
	pair<long double, long double> limites(INF, -INF);
	
	for (int i = 0; i < (int)seg1.size(); i++)//olha a interseccao de todos os segmentos do asteroid 1 com o segmento do VERTICE do asteroid2
	{
		if(paralelos(seg1[i], segAt)){
			if(taNoSegmento(seg1[i].a, segAt)){
				//~ printf("oi\n");
				dist = min(getDistPt(segAt.a, seg1[i].a), getDistPt(segAt.b, seg1[i].b));//ve qual vertice do segmento do asteroid1 ele toca primeiro, pq sao paralelos
				tempo = dist * 1.0 / NORMA_VEL;
				limites.F = min(limites.F, tempo);
				limites.S = max(limites.S, tempo);
				if(tempo > eps) tempos.pb(tempo);
			}
		}else{
			if(temInterseccaoSegInt(seg1[i], segAt)){
				
				pt = getPontoInterseccaoSeg(seg1[i], segAt);
				//~ printf("\nSegmentos:\n"); printaPonto(seg1[i].a); printaPonto(seg1[i].b);
				//~ printf("e:\n"); printaPonto(segAt.a); printaPonto(segAt.b);
				//~ printf("Se interceptam no ponto: "); printaPonto(pt);
				
				dist = getDistPt(pt, a);
				tempo = dist * 1.0 / NORMA_VEL;
				
				limites.F = min(limites.F, tempo);
				limites.S = max(limites.S, tempo);
				if(tempo > eps) tempos.pb(tempo);
			}
		}
	}
	//~ printf("Vertice ");
	//~ printaPonto(a);
	//~ printf("Tem os tempos [%.4Lf, %.4Lf]\n\n", limites.F, limites.S);
	return limites;
}



pair<long double, long double> getEstado(){
	//passa em todos os vertices do asteroid 2, vendo onde cada vertice do asteroid 1 ta
	int tem[6];
	memset(tem, 0, sizeof tem);
	int tipo;
	int cnt = 0;
	
	for (int i = 0; i < (int)asteroid2.size(); i++)
	{
		tipo = getTipoVertice(i);
		//~ printf("Vertice %d do asteroid 2: ", i);
		//~ printaPonto(asteroid2[i]);
		//~ printf("Tipo: ");
		//~ printaTipo(tipo);
		tem[tipo]++;
	}
	
	
	if(tem[3] == (int)asteroid2.size() || tem[4] == (int)asteroid2.size()){//nao toca/cruza
		//~ printf("AAAAAH\n");
		return mp(1.0, -1.0);
	}
	
	pair<long double, long double> limites(INF, -INF);
	pair<long double, long double> at;
	for (int i = 0; i < (int)asteroid2.size(); i++)//pegar o tempo q entra e o tempo q sai do outro asteroid
	{
		at = getTempo(asteroid2[i]);
		limites.F = min(limites.F, at.F);
		limites.S = max(limites.S, at.S);
	}
	
	//
	seg1.clear();
	for (int i = 0; i < (int)asteroid2.size(); i++)
	{
		seg1.pb(segmento(asteroid2[i], asteroid2[(i+1)%(int)asteroid2.size()]));
	}
	vel = vel1 + (vel2 * -1);
	//~ printf("NOVA VEL: "); printaPonto(vel);
	NORMA_VEL = norma(vel);
	for (int i = 0; i < (int)asteroid1.size(); i++)
	{
		at = getTempo(asteroid1[i]);
		limites.F = min(limites.F, at.F);
		limites.S = max(limites.S, at.S);
	}
	
	//
	if(tem[1] > 0 && tem[3] > 0 && (tem[1] + tem[3] == (int)asteroid2.size()))//toca
		return mp(-1.0, limites.F);
	if(tem[2] > 0 && tem[4] > 0 && (tem[2] + tem[4] == (int)asteroid2.size()))//toca
		return mp(-1.0, limites.F);
		
	return limites;//cruza
}

long double area(){
	long double ans=0.0;
	poligono.pb(poligono[0]);
	for(int i=0; i<poligono.size()-1; i++){
		ans += crossDouble(poligono[i], poligono[i+1]);
	}
	return fabs(ans)*0.5;
}

bool ccw(pv a, pv b, pv c){
	return crossDouble(b-a, c-b) > eps;
}

long double getAngle(pv a, pv p, pv b){
	pv u = a-p;
	pv v = b-p;
	
	long double angle = acos(dotDouble(u, v) / (norma(u) * norma(v)));
	if(ccw(a, p, b)) angle = -angle;
	
	return angle;
}

bool dentro(pv p){
	long double angle = 0.0;
	bool dentro1 = true;
	bool dentro2 = true;
	int sz = (int)copiaAsteroid2.size();
	
	int dir = 0;
	int esq = 0;
	int centro = 0;
	long double c;
	for (int i = 0; i < sz; i++)
	{
		c = crossDouble(copiaAsteroid2[i] - p, copiaAsteroid2[(i+1)%sz] - p);
		if(c > eps) dir++;
		else if(c < -eps) esq++;
		else centro++;
	}
	if(esq && dir) dentro1 = false;
	
	dir = 0; esq = 0; centro = 0;
	sz = (int)asteroid1.size();
	
	for (int i = 0; i < sz; i++)
	{
		c = crossDouble(asteroid1[i] - p, asteroid1[(i+1)%sz] - p);
		if(c > eps) dir++;
		else if(c < eps) esq++;
		else centro++;
	}
	if(esq && dir) dentro2 = false;
	
	return dentro1 && dentro2;
}

void CH(){
	pv p1[100];
	pv p2[100];
	int sz1 = 0;
	int sz2 = 0;
	
	sort(poligono.begin(), poligono.end());
	for (int i = 0; i < poligono.size(); i++)
	{
		if(i>0 && poligono[i] == poligono[i-1]){
			//~ printf("IGUAL "); printaPonto(poligono[i]);
			continue;
		}
		while(sz1 > 1 && ccw(p1[sz1-2], p1[sz1-1], poligono[i]))
		{
			sz1--;
		}
		p1[sz1++] = poligono[i];
		
		while (sz2 > 1 && !ccw(p2[sz2-2], p2[sz2-1], poligono[i]))
		{
			sz2--;
		}
		p2[sz2++] = poligono[i];
		
	}
	//~ printf("UPPER\n");
	//~ for (int i = 0; i < sz1; i++)
	//~ {
		//~ printaPonto(p1[i]);
	//~ }
	//~ printf("LOWER\n");
	//~ for (int i = 0; i < sz2; i++)
	//~ {
		//~ printaPonto(p2[i]);
	//~ }
	
	
	poligono.clear();
	for (int i = 0; i < sz1; i++)
	{
		poligono.pb(p1[i]);
		
	}
	
	for (int i = sz2-2; i >= 1; i--)
	{
		poligono.pb(p2[i]);
	}
	
}

long double getAreaInterPoly(long double tempo){
	seg2.clear();
	pv a, b;
	//~ printf("TEMPO = %.10Lf\n", tempo);
	
	copiaAsteroid2.clear();
	vector<segmento> geral;
	
	//~ printf("\n================================\nPONTOS NOVOS DO ASTEROID 2\n");
	for (int i = 0; i < (int)asteroid2.size(); i++)
	{
		a = asteroid2[i] + (vel * tempo);
		copiaAsteroid2.pb(a);
		//~ printaPonto(a);
		b = asteroid2[(i+1)%(int)asteroid2.size()] + (vel * tempo);
		geral.pb(segmento(a, b));
	}
	//~ printf("================================\n\n");
	pv pt;
	poligono.clear();
	
	for (int i = 0; i < (int)seg1.size(); i++)
	{
		geral.pb(seg1[i]);
	}
	
	
	int sz1 = (int)seg1.size();
	int sz2 = (int)seg2.size();
	int sz = (int)geral.size();
	
	
	for (int i = 0; i < sz; i++)
	{
		
		for (int j = i+1; j < sz; j++)
		{
			if(paralelos(geral[i], geral[j])){
				//FAZER
				if(taNoSegmento(geral[i].a, geral[j])){
					if(dentro(geral[i].a)){
						poligono.pb(geral[i].a);
					}
				}
				if(taNoSegmento(geral[i].b, geral[j])){
					if(dentro(geral[i].b)){
						poligono.pb(geral[i].b);
					}
				}
				
				if(taNoSegmento(geral[j].a, geral[i])){
					if(dentro(geral[j].a)){
						poligono.pb(geral[j].a);
					}
				}
				if(taNoSegmento(geral[j].b, geral[i])){
					if(dentro(geral[j].b)){
						poligono.pb(geral[j].b);
					}
				}
			}else{
				
				if(temInterseccaoSegDouble(geral[i], geral[j])){
					pt = getPontoInterseccaoSeg(geral[i], geral[j]);
					if(dentro(pt)){
						poligono.pb(pt);
					}
				}
				
			}
		}
	}
	CH();
	//~ printf("CH\n");
	//~ for (int i = 0; i < poligono.size(); i++)
	//~ {
		//~ printaPonto(poligono[i]);
	//~ }
	
	return area();
}

long double solve(){
	pair<long double, long double> range = getEstado();
	if(range.F > eps && range.S < -eps) return -1.0;
	if(range.F < -eps && range.S > eps) return range.S;
	
	long double lo = range.F;
	long double hi = range.S;
	long double mid1, mid2, inter1, inter2;
	long double maxArea = -1.0, minTime = INF;
	
	vel = vel2 + (vel1 * -1);
	NORMA_VEL = norma(vel);
	
	seg1.clear();
	for (int i = 0; i < (int)asteroid1.size(); i++)
	{
		seg1.pb(segmento(asteroid1[i], asteroid1[(i+1)%(int)asteroid1.size()]));
	}
	
	
	//~ printf("RANGE DE BUSCA = [%.4Lf, %.4Lf]\n", lo, hi);
	//~ if(lo >= 100000000000000000000.0) return INF;
	//~ cout << fixed << setprecision(10) << getAreaInterPoly(4.193518) << endl;
	//~ cout << fixed << setprecision(10) << getAreaInterPoly(4.1924372281) << endl;
	//~ cout << fixed << setprecision(10) << getAreaInterPoly(4.1679012346) << endl;
	//~ cout << fixed << setprecision(10) << getAreaInterPoly(4.1935140642) << endl;
	//~ cout << getAreaInterPoly(1) << endl;
	//~ cout << getAreaInterPoly(2) << endl;
	//~ cout << "3.5 - " << fixed << setprecision(10) << getAreaInterPoly(3.5) << endl;
	//~ cout << "3.999966 - " << fixed << setprecision(10) << getAreaInterPoly(3.999966) << endl;
	//~ cout << "4.0 - " << fixed << setprecision(10) << getAreaInterPoly(4) << endl;
	//~ cout << getAreaInterPoly(1.9999999990) << endl;
	
	//~ for (long double i = 4.193514; i <= 4.193519; i+=0.000001)
	//~ {
		//~ cout << "tempo = " << i << " " << getAreaInterPoly(i) << "\n";
	//~ }
	
	int lim = 200;
	sort(tempos.begin(), tempos.end());
	//~ printf("tempos = %d\n", tempos.size());
	for (int i = 0; i < tempos.size()-1; i++)
	{
		lo = tempos[i];
		hi = tempos[i+1];
		inter1 = getAreaInterPoly(tempos[i]);
		if(inter1 > eps+maxArea){
			maxArea = inter1;
			minTime = tempos[i];
		}else if(fabs(inter1 - maxArea) < eps){
			minTime = min(minTime, mid1);
		}
		//~ cout << tempos[i] << endl;
		for (int j = 0; j < 200; j++)
		{
			mid1 = (2*lo + hi)/3.0;
			mid2 = (lo + 2*hi)/3.0;
			//~ printf("lo = %.5Lf  hi = %.5Lf\n", lo, hi);
			//~ printf("mid1 = %.5Lf   mid2 = %.5Lf\n", mid1, mid2);
			inter1 = getAreaInterPoly(mid1);
			inter2 = getAreaInterPoly(mid2);
			
			//~ printf("AREA1 = %.10Lf tempo = %.10Lf\n", inter1, mid1);
			//~ printf("AREA2 = %.10Lf tempo = %.10Lf\n\n", inter2, mid2);
			//~ if(fabs(inter1 - inter2) < eps) return min(mid1, minTime);
			
			if(inter1+eps < inter2){//CUIDADO
				if(inter2 > eps+maxArea){
					maxArea = inter2;
					minTime = mid2;
				}else if(fabs(inter2 - maxArea) < eps){
					minTime = min(minTime, mid2);
				}
				lo = mid1;
			}else{
				if(inter1 > eps+maxArea){
					maxArea = inter1;
					minTime = mid1;
				}else if(fabs(inter1 - maxArea) < eps){
					minTime = min(minTime, mid1);
				}
				hi = mid2;
			}
		}
		
		
	}
	
	return minTime;
}


int main(){
	//~ cout << paralelos(segmento(pv(0,0), pv(10,0)), segmento(pv(1,1), pv(20,1))) << "\n";
	//~ cout << taNoSegmento(pv(3,0), segmento(pv(1,0), pv(20,0))) << "\n";
	int n;
	//~ cout << temInterseccaoSegDouble(segmento(pv(14, -1), pv(10,3)), segmento(pv(6,2), pv(3,2))) << endl;
	ll x, y;
	while(cin >> n){
		asteroid1.clear();
		asteroid2.clear();
		copiaAsteroid2.clear();
		poligono.clear();
		seg1.clear();
		seg2.clear();
		tempos.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			asteroid1.pb(pv((long double)x, (long double)y));
		}
		cin >> x >> y;
		vel1 = pv((long double)x, (long double)y);
		
		for (int i = 0; i < n; i++)
		{
			seg1.pb(segmento(asteroid1[i], asteroid1[(i+1)%n]));
		}
		
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			asteroid2.pb(pv((long double)x, (long double)y));
		}
		cin >> x >> y;
		vel2 = pv((long double)x, (long double)y);
		
		vel = vel2 + (vel1 * -1);
		NORMA_VEL = norma(vel);
		
		long double ans = solve();
		if(ans >= INF-1.0) ans = -1.0;
		if(ans < 0) cout << "never\n";
		else cout << fixed << setprecision(12) << ans << "\n";
	}
	
	return 0;
}
