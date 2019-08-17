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

bool podeAdicionarVertice(vector<pv> &polygon, pv pt){
	if((int)polygon.size() == 0) return true;
	if(polygon[(int)polygon.size()-1] == pt) return false;
	return true;
}

//funcao que corta o poligono (retorna o primeiro ponto igual ao primeiro)
int cutPolygon(line r, vector<pv> &polygon, vector<pv> &leftPart, vector<pv> &rightPart){//0 - fora   1 - cortou
	if(!(polygon[0] == polygon[(int)polygon.size()-1]))
		polygon.pb(polygon[0]);
	
	seg corte = seg(pv(r.p0.x+1000000*r.v.x, r.p0.y+1000000*r.v.y), pv(r.p0.x-1000000*r.v.x, r.p0.y-1000000*r.v.y));//CUIDADO COM OS LIMITES
	int esq = 0, dir = 0, centro = 0;
	leftPart.clear();
	rightPart.clear();
	int c;
	int tem;
	pv pt;
	
	//~ printf("Corte = "); printaPonto(corte.a); cout << " "; printaPonto(corte.b); cout << endl;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		if(retasIguais(line(polygon[i], polygon[i+1] - polygon[i]), r)){//corta na borda
			//~ printf("Cortou na borda\n");
			return 0;
		}
		
		tem = interSegmento(seg(polygon[i], polygon[i+1]), corte, pt);
		
		c = sinal(cross(r.v, polygon[i] - r.p0));
		
		if(c > 0){
			if(podeAdicionarVertice(leftPart, polygon[i]))
				leftPart.pb(polygon[i]);
			esq++;
		}
		else if(c < 0){
			if(podeAdicionarVertice(rightPart, polygon[i]))
				rightPart.pb(polygon[i]);
			dir++;
		}
		else{
			if(podeAdicionarVertice(leftPart, polygon[i]))
				leftPart.pb(polygon[i]);
			if(podeAdicionarVertice(rightPart, polygon[i]))
				rightPart.pb(polygon[i]);
			centro++;
		}
		
		if(tem == 1){//tem interseccao com o segmento e é única
			//~ printf("achei interseccao no ponto = "); printaPonto(pt); cout << endl;
			if(podeAdicionarVertice(leftPart, pt))
				leftPart.pb(pt);
			if(podeAdicionarVertice(rightPart, pt))
				rightPart.pb(pt);
		}
	}
	if(esq == (int)polygon.size()-1) return 0;//todos do mesmo lado
	if(dir == (int)polygon.size()-1) return 0;//todos do mesmo lado
	
	if(esq == (int)polygon.size()-2 && centro==1) return 0;//1 no corte e todos os outros do outro lado
	if(dir == (int)polygon.size()-2 && centro==1) return 0;//1 no corte e todos os outros do outro lado
	
	//~ for (int i = 0; i < polygon.size()-1; i++)
	//~ {
		
	//~ }
	//~ printf()
	if(!(leftPart[0] == leftPart[(int)leftPart.size()-1])) leftPart.pb(leftPart[0]);
	if(!(rightPart[0] == rightPart[(int)rightPart.size()-1])) rightPart.pb(rightPart[0]);
	
	
	return 1;
	
}

int main(){
	int n, larg, alt;
	ld x, y, x0, y0;
	pv local;
	vector<pv> polygon, lp, rp;
	int res;
	int caso = 1;
	while (cin >> n >> larg >> alt >> x >> y)
	{
		polygon.clear();
		
		local = pv(x, y);
		polygon.pb(pv(0, 0));
		polygon.pb(pv(larg, 0));
		polygon.pb(pv(larg, alt));
		polygon.pb(pv(0, alt));
		
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> x0 >> y0;
			res = cutPolygon(line(pv(x, y), pv(x0, y0) - pv(x, y)), polygon, lp, rp);
			if(res == 1){
				if(insidePolygonLogN(local, lp)) polygon = lp;
				else polygon = rp;
			}
		}
		cout << "Case #" << caso++ << ": " << fixed << setprecision(3) << area(polygon) << "\n";
	}
	
	
	return 0;
}
