#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef double ld;
#define EPS 1e-9
#define PI acos(-1)


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


//OKKKKKKK
ld distPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

//OKKKKKK
ld cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

//OKKKKKK
ld dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}

//angulo entre a reta horizontal com y = 0 e o vetor v      OKKKKKK
ld polarAngle(pv v){
	ld x = v.x;
	ld y = v.y;
	
	ld aux = atan2(y, x);
	
	if(menor(aux, 0.0)) aux += 2.0*PI;
	
	return aux;
}

//radiano para grau   OKKKKKK
ld toDegree(ld rad){
	return rad * 180 / PI;
}

//norma de um vetor  OKKKKKK
ld norma(pv a){
	return sqrt(dot(a, a));
}

//angulo entre dois vetores (menor angulo)     OKKKKKK
ld angle2Vec(pv v, pv u){
	ld ang1 = polarAngle(v);
	ld ang2 = polarAngle(u);
	ld ans = 0.0;
	
	ans = min(fabs(ang1 - ang2), fabs(2.0*PI+ang1 - ang2));
	ans = min(ans, fabs(2.0*PI+ang2 - ang1));

	return ans;
}

//checa se os pontos a, b, c estão em sentido anti horário  OKKKKKK
bool ccw(pv a, pv b, pv c){
	ld aux = cross(b-a, c-b);
	
	return maior(aux, 0.0);
}

//checa se ponto p está no segmento s   OKKKK
bool onSegment(pv p, seg s){
	pv a = s.a;
	pv b = s.b;
	if(maiorIgual(dot(p-a, b-a), 0.0) && maiorIgual(dot(p-b, a-b), 0.0) && igual(cross(p-a, p-b), 0.0)) return true;
	return false;
}

//calcula o perimetro de um poligono       OKKKKK
ld perimetro(vector<pv> &polygon){
	if((int)polygon.size()<=1) return 0.0;
	
	if(!(polygon[0] == polygon[(int)polygon.size()-1]))
		polygon.pb(polygon[0]);
	
	ld ans = 0.0;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		ans += distPt(polygon[i], polygon[i+1]);
	}
	return ans;
}

//calcula a area de um poligono    OKKKKKKK
ld area(vector<pv> &polygon){
	if((int)polygon.size()<=2) return 0.0;
	
	if(!(polygon[0] == polygon[(int)polygon.size()-1]))
		polygon.pb(polygon[0]);
	
	ld ans = 0.0;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		ans += cross(polygon[i], polygon[i+1]);
	}
	return fabs(ans)*0.5;
}

//ordena por x, se empatar por y     OKKKKKK
bool compareConvexHull(pv a, pv b){
	if(igual(a.x, b.x)) return menor(a.y, b.y);
	return menor(a.x, b.x);
}

//OKKKKKKK
bool colinear(pv a, pv b, pv c){
	return igual(cross(b-a, c-b), 0.0);
}
//gera a convex hull do vector pt    OKKKK
void convexHull(vector<pv> &polygon){
	if((int)polygon.size() <= 2) return;
	pv p1[(int)polygon.size() + 2];
	pv p2[(int)polygon.size() + 2];
	int sz1 = 0, sz2 = 0;
	
	sort(polygon.begin(), polygon.end(), compareConvexHull);
	for (int i = 0; i < (int)polygon.size(); i++)
	{
		if(i && polygon[i] == polygon[i-1]) continue;
		while (sz1 > 1 && ccw(p1[sz1-2], p1[sz1-1], polygon[i]))
		{
			sz1--;
		}
		p1[sz1++] = polygon[i];
		
		while (sz2 > 1 && !ccw(p2[sz2-2], p2[sz2-1], polygon[i]))
		{
			sz2--;
		}
		p2[sz2++] = polygon[i];
	}
	
	vector<pv> tmp;
	
	for (int i = 0; i < sz1; i++)
	{
		tmp.pb(p1[i]);
	}
	for(int i = sz2-2; i>=1; i--){
		tmp.pb(p2[i]);
	}
	tmp.pb(tmp[0]);
	polygon.clear();
	
	polygon.pb(tmp[0]);
	//TIRA PONTOS COLINEARES
	for (int i = 1; i < tmp.size()-1; i++)
	{
		if(colinear(tmp[i-1], tmp[i], tmp[i+1])) continue;
		polygon.pb(tmp[i]);
	}
	
	//~ polygon.pb(polygon[0]);
}

//checar se ponto esta dentro de poligono em O(n) - comparação de ângulo    OKKK
bool insidePolygon(pv p, vector<pv> &polygon){
	if((int)polygon.size()<= 2) return false;
	
	if(!(polygon[0] == polygon[(int)polygon.size()-1])){
		polygon.pb(polygon[0]);
	}
	bool naBorda = false;
	
	ld ang = 0.0;
	for (int i = 0; i < polygon.size()-1; i++)
	{
		naBorda = naBorda || onSegment(p, seg(polygon[i], polygon[i+1]));
		if(ccw(p, polygon[i], polygon[i+1])){
			ang += angle2Vec(polygon[i] - p, polygon[i+1]-p);
		}else{
			ang -= angle2Vec(polygon[i] - p, polygon[i+1]-p);
		}
	}
	return igual(fabs(ang), 2.0*PI) || naBorda;//se quiser totalmente dentro tem que tirar || naBorda
}




//função pra ordenar em relação ao angulo polar só com cross OKKKKKK
bool comparePolarAngle(pv a, pv b){
	if(a == b){
		return true;//pontos iguais
	}
	pv origem = pv(0, 0);
	if(a == origem){
		return true;
	}
	if(b == origem){
		return false;
	}
	
	if(igual(a.y, 0.0) && igual(b.y, 0.0)){//ambos no eixo x
		if(menor(a.x, 0.0) && maior(b.x, 0.0)){
			return false;
		}
		if(maior(a.x, 0.0) && menor(b.x, 0.0)){
			return true;
		}
		
		//lados opostos
		if(menor(distPt(origem, a), distPt(origem, b))){
			return true;
		}
		return false;
	}
	if(igual(a.y, 0.0)){
		if(maior(a.x, 0.0)){//pra direita
			return true;
		}else{//pra esquerda
			if(maior(b.y, 0.0)){
				return false;
			}
			return true;
		}
	}
	
	if(igual(b.y, 0.0)){
		if(maior(b.x, 0.0)){
			return false;
		}else{
			if(maior(a.y, 0.0)){
				return true;
			}
			return false;
		}
	}
	//nesse momento nenhum está com y == 0
	if(maior(a.y, 0.0) && menor(b.y, 0.0)){
		return true;
	}
	if(menor(a.y, 0.0) && maior(b.y, 0.0)){
		return false;
	}
	
	if(colinear(origem, a, b)){
		if(menor(distPt(origem, a), distPt(origem, b))){
			return true;
		}
		return false;
	}
		
	if(maior(cross(b-origem, a-origem), 0.0)){
		return false;
	}
	return true;
}

//retorna o sinal de um número OKKK
int sinal(ld res){
	if(maior(res, 0.0)) return 1;
	if(menor(res, 0.0)) return -1;
	return 0;
}

//checa se duas retas são paralelas       OKKKK
bool retasParalelas(line r, line s){
	pv v = r.v;
	pv u = s.v;
	return igual(cross(v, u), 0.0);
}

//checa se duas retas são iguais     OKKKK 
bool retasIguais(line r, line s){
	pv p0 = r.p0;
	pv p1 = s.p0;
	pv v = r.v;
	pv u = s.v;
	
	return retasParalelas(r, s) && igual(cross(v, p1-p0), 0.0);
}

//checa se 2 segmentos se cruzam (pode ser na borda)   OKKKK
bool temInterSegmento(seg r, seg s){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	
	return sinal(cross(b-a, d-a)) != sinal(cross(b-a, c-a)) && sinal(cross(d-c, a-c)) != sinal(cross(d-c, b-c));
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

//checa se tem interseccao entre segmentos (0 - nao tem, 1 - tem, 2 - paralelos (SE TOCAM MAS NAO RETORNA O PONTO) )   OKKK
int interSegmento(seg r, seg s, pv &ans){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	if(retasIguais(line(a, b-a), line(c, d-c))){
		
		if(onSegment(c, r) || onSegment(d, r) || onSegment(a, s) || onSegment(b, s)){
			return 2;
		}
		return 0;
	}
	if(temInterSegmento(r, s)){
		ans = ptInterReta(line(a, b-a), line(c, d-c));
		return 1;
	}
	return 0;
}

//checa se um ponto esta dentro de um triangulo (a, b, c)   OKKK
bool insideTriangle(pv p, pv a, pv b, pv c){
	if(onSegment(p, seg(a, b))) return true;
	if(onSegment(p, seg(a, c))) return true;
	if(onSegment(p, seg(b, c))) return true;
	
	return sinal(cross(b-a, p-a)) == sinal(cross(c-b, p-b)) && sinal(cross(c-b, p-b)) == sinal(cross(a-c, p-c));
}

//checa se um ponto esta dentro de um polígono em O(log n)   OKKKKK
bool insidePolygonLogN(pv p, vector<pv> &polygon){//NAO PODE TER PONTOS COLINEARES
	if((int)polygon.size() == 0) return false;
	
	int sz;
	if(polygon[0] == polygon[(int)polygon.size()-1]) sz = (int)polygon.size()-1;
	else sz = (int)polygon.size();
	
	if(sz <= 2) return false;
	
	if(ccw(polygon[0], polygon[1], polygon[2])){
		if(!(polygon[0] == polygon[(int)polygon.size()-1])) polygon.pb(polygon[0]);
		reverse(polygon.begin(), polygon.end());
	}
	
	int lo = 1, hi = sz-1, mid;
	int c;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		c = sinal(cross(polygon[mid] - polygon[0], p - polygon[0]));
		if(c < 0){
			lo = mid+1;
		}else if(c > 0){
			hi = mid-1;
		}else{
			if(mid == 1){
				return insideTriangle(p, polygon[0], polygon[mid], polygon[mid+1]);
			}else{
				return insideTriangle(p, polygon[0], polygon[mid-1], polygon[mid]);
			}
		}
	}
	mid = (lo+hi)/2;
	if(mid == 0 || mid == sz-1) return false;
	
	return insideTriangle(p, polygon[0], polygon[mid], polygon[mid+1]);
}

void printaPonto(pv a){
	printf("(%.2Lf, %.2Lf)  ", a.x, a.y);
	
}

//retorna a interseccao dos poligonos  OKKKKK
int interPolygon(vector<pv> &polygon1, vector<pv>& polygon2, vector<pv> &interseccao){
	
	if(!(polygon1[0] == polygon1[(int)polygon1.size() - 1])) polygon1.pb(polygon1[0]);
	if(!(polygon2[0] == polygon2[(int)polygon2.size() - 1])) polygon2.pb(polygon2[0]);
	interseccao.clear();
	
	bool tem = false;
	vector<seg> segmentos;
	pv pt;
	
	for (int i = 0; i < (int)polygon1.size()-1; i++)
	{
		segmentos.pb(seg(polygon1[i], polygon1[i+1]));
	}
	for (int i = 0; i < (int)polygon2.size()-1; i++)
	{
		segmentos.pb(seg(polygon2[i], polygon2[i+1]));
	}
	
	int res;
	for (int i = 0; i < (int)segmentos.size(); i++)
	{
		for (int j = i+1; j < (int)segmentos.size(); j++)
		{
			res = interSegmento(segmentos[i], segmentos[j], pt);
			if(res == 1){
				if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
					interseccao.pb(pt);
					tem = true;
				}
			}else if(res == 2){
				if(onSegment(segmentos[i].a, segmentos[j])){
					pt = segmentos[i].a;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
				if(onSegment(segmentos[i].b, segmentos[j])){
					pt = segmentos[i].b;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
				if(onSegment(segmentos[j].a, segmentos[i])){
					pt = segmentos[j].a;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
				if(onSegment(segmentos[j].b, segmentos[i])){
					pt = segmentos[j].b;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
			}
		}
		
	}
	if(!tem) return false;
	
	convexHull(interseccao);
	
	return true;
}

//funcao usada na cutPolygon para não repetir vértices em um corte
void adiciona(vector<pv> &polygon, pv pt){
	if((int)polygon.size() == 0){
		polygon.pb(pt);
	}else{
		if(!(polygon[(int)polygon.size()-1] == pt))
			polygon.pb(pt);
	}
}


//NAO ACEITA PONTOS COLINEARES
//0 - não cortou ou cortou na borda
//1 - as duas partes tem area
int cutPolygon(line r, vector<pv> &polygon, vector<pv> &lp, vector<pv> &rp){
	if(!(polygon[0] == polygon[(int)polygon.size()-1])) 
		polygon.pb(polygon[0]);
	
	lp.clear();
	rp.clear();
	int lado;
	
	int cortou = 0;
	pv pt;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		lado = sinal(cross(r.v, polygon[i] - r.p0));
		
		//teste de ponto
		if(lado == 1){//esta à esquerda da linha
			adiciona(lp, polygon[i]);
			//~ printf("Ponto ta na esquerda"); printaPonto(polygon[i]);
			//~ cout << endl;
		}else if(lado == -1){//esta à direita da linha
			adiciona(rp, polygon[i]);
			//~ printf("Ponto ta na direita"); printaPonto(polygon[i]);
			//~ cout << endl;
		}
		
		//teste de intersecção
		if(sinal(cross(r.v, polygon[i] - r.p0)) != sinal(cross(r.v, polygon[i+1] - r.p0))){//segmento está inteiro na reta (cortou na borda)
			//nao faz nada pois os dois vertices serão adicionados na verificacao acima
			cortou = 1;
			pt = ptInterReta(line(polygon[i], polygon[i+1]-polygon[i]), r);
			//~ printf("Ponto de interseccao = %d-%d ", i, i+1); printaPonto(pt);
			//~ cout << endl;
			adiciona(lp, pt);
			adiciona(rp, pt);
		}
	}
	if((int)lp.size() > 2) adiciona(lp, lp[0]);
	if((int)rp.size() > 2) adiciona(rp, rp[0]);
	return cortou;
}

vector<pair<int, ld> > g[6000];
vector<seg> segmento;
int n;
ld dist[6000];
char vis[6000];


void reset(){
	
	int x = ((int) segmento.size())*2 + 20;
	for (int i = 0; i < x; i++) 
	{
		g[i].clear();
	}
	segmento.clear();
}

void add_edge(int i, int j, ld w){
	g[i].pb(mp(j, w));
	g[j].pb(mp(i, w));
	//~ printf("aresta de %d para %d   %Lf\n", i, j, w); 
}

bool ok(seg r){
	bool tem = false;
	pv pt;
	int aux;
	
	for (int i = 0; i < (int)segmento.size(); i++)
	{
		aux = interSegmento(r, segmento[i], pt);
		if(aux == 1){
			if(!(pt==r.a || pt==r.b || pt==segmento[i].a || pt==segmento[i].b)){
				tem = true;
			}
		}
		if(tem) return false;
	}
	if(tem) return false; 
	return true;
}

ld dij(int o, int d){
	for (int i = 0; i < (int)segmento.size() * 3; i++)
	{
		dist[i] = 100000000000000000.0;
		vis[i] = 0;
	}
	
	
	priority_queue<pair<ld, int>, vector<pair<ld, int> >, greater<pair<ld, int> > > pq;
	pq.push(mp(0, o));
	dist[o] = 0.0;
	
	int u, v;
	ld w;
	while (!pq.empty())
	{
		u = pq.top().S;
		pq.pop();
		if(u==d){
			//~ printf("oi\n", dist[d]);
			return dist[d];
		}
		if(vis[u]) continue;
		vis[u] = 1;
		//~ printf("estou em %d\n", u);
		for (int i = 0; i < g[u].size(); i++)
		{
			v = g[u][i].F;
			w = g[u][i].S;
			if(menor(dist[u] + w, dist[v])){
				dist[v] = dist[u] + w;
				pq.push(mp(dist[v], v));
			}
		}
		
	}
	
}

int main(){
	ld xi, yi, xf, yf;
	pv origem, destino;
	while (cin >> xi >> yi >> xf >> yf >> n)
	{
		if(!xi && !yi && !xf && !yf && !n) break;
		
		origem = pv(xi, yi);
		destino = pv(xf, yf);
		reset();
		
		
		segmento.pb(seg(origem, origem));
		segmento.pb(seg(destino, destino));
		
		for (int i = 0; i < n; i++)
		{
			cin >> xi >> yi >> xf >> yf;
			segmento.pb(seg(pv(xi, yi), pv(xf, yf)));
		}
		int sz = (int)segmento.size();
		
		for (int i = 0; i < sz; i++)
		{
			for (int j = i+1; j < sz; j++)
			{
				if(i==j) continue;
				//~ printf("i = %d j = %d\n", i, j);
				if(ok(seg(segmento[i].a, segmento[j].a))){
					add_edge(i*2, j*2, distPt(segmento[i].a, segmento[j].a));
					//~ printf("aresta de "); printaPonto(segmento[i].a); printf(" e "); printaPonto(segmento[j].a); printf("\n");
				}
				if(ok(seg(segmento[i].a, segmento[j].b))){
					add_edge(i*2, j*2 + 1, distPt(segmento[i].a, segmento[j].b));
					//~ printf("aresta de "); printaPonto(segmento[i].a); printf(" e "); printaPonto(segmento[j].b); printf("\n");
				}
				if(ok(seg(segmento[i].b, segmento[j].a))){
					add_edge(i*2 + 1, j*2, distPt(segmento[i].b, segmento[j].a));
					//~ printf("aresta de "); printaPonto(segmento[i].b); printf(" e "); printaPonto(segmento[j].a); printf("\n");
				}
				if(ok(seg(segmento[i].b, segmento[j].b))){
					add_edge(i*2 + 1, j*2 + 1, distPt(segmento[i].b, segmento[j].b));
					//~ printf("aresta de "); printaPonto(segmento[i].b); printf(" e "); printaPonto(segmento[j].b); printf("\n");
				}
			}
			
		}
		cout << fixed << setprecision(2) << dij(0*2, 1*2) << "\n";
	}
	
	
	return 0;
}
