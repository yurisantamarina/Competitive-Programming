#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010

typedef long long int ll;

struct pv{
	int x, y, id;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	pv(int a, int b, int c){
		x = a;
		y = b;
		id = c;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y, id);
	}
	int operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	int operator * (pv other) const{
		return x * other.x + y * other.y;
	}
	int nsq(){
		return (*this) * (*this);
	}
	bool operator < (pv other) const{
		if(x != other.x) return x < other.x;
		return y < other.y;
	}
};

struct circle{
	pv centro;
	int raio;
	circle(){}
	circle(pv a, int b){
		centro = a;
		raio = b;
	}
};

double eps = 1e-9, PI = acos(-1);
vector<pv> pts, informante, copiaInformante, country;
vector<circle> radar;
vector<vector<pv> > chs;
int seen[MAXN], d[MAXN], low[MAXN], tempo = 1, B, N, M;
int pilha[MAXN], len = 0;
pv p1[MAXN], p2[MAXN];
vector<int> g[MAXN];
bool inside[MAXN];

ll dist2(pv a, pv b){
	ll A = (a.x - b.x);
	ll B = (a.y - b.y);
	return A * A + B * B;
}

pair<ll, ll> distPtSeg2(pv p, pv a, pv b){
	if(((p - a) * (b - a)) >= 0 && ((p - b) * (a - b)) >= 0){
		ll area = abs((p - a) ^ (b - a));
		ll num = area * area;
		ll den = (b - a).nsq();
		
		ll g = __gcd(num, den);
		return {num / g, den / g};
	}
	
	return {min(dist2(p, a), dist2(p, b)), 1};
}

void removeInsideRadar(){
	memset(inside, false, sizeof inside);
	informante.clear();
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++)
			if(dist2(copiaInformante[i], radar[j].centro) <= radar[j].raio * radar[j].raio){
				inside[i] = true;
				break;
			}
			
		if(!inside[i])
			informante.push_back(copiaInformante[i]);
	}
	
	N = (int)informante.size();
	copiaInformante.clear();
	for (int i = 0; i < N; i++)
		copiaInformante.push_back(informante[i]);
		
	//~ for(pv a : informante){
		//~ printf("(%d, %d)\n", a.x, a.y);
	//~ }
}

void buildGraph(){
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			if(i != j && dist2(radar[i].centro, radar[j].centro) <= (radar[i].raio + radar[j].raio) * (radar[i].raio + radar[j].raio)){
				g[i].push_back(j);
				//~ printf("%d %d\n", i, j);
			}
}

//angulo entre a reta horizontal com y = 0 e o vetor v
double polarAngle(pv v){
	int x = v.x;
	int y = v.y;
	
	double aux = atan2(y, x);
	
	if(aux < -eps) aux += 2.0*PI;
	
	return aux;
}

//angulo entre dois vetores (menor angulo)     
double angle2Vec(pv v, pv u){
	double ang1 = polarAngle(v);
	double ang2 = polarAngle(u);
	double ans = 0.0;
	
	ans = min(fabs(ang1 - ang2), fabs(2.0*PI+ang1 - ang2));
	ans = min(ans, fabs(2.0*PI+ang2 - ang1));

	return ans;
}

//checa se os pontos a, b, c estão em sentido anti horário  
bool ccw(pv a, pv b, pv c){
	double aux = (b-a) ^ (c-b);
	
	return aux > eps;
}

//checar se ponto esta dentro de poligono em O(n) - comparação de ângulo    
bool insidePolygon(pv p, vector<pv> &polygon){
	polygon.push_back(polygon[0]);
	double ang = 0.0;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		if(ccw(p, polygon[i], polygon[i+1])){
			ang += angle2Vec(polygon[i] - p, polygon[i+1]-p);
		}else{
			ang -= angle2Vec(polygon[i] - p, polygon[i+1]-p);
		}
	}
	return fabs(fabs(ang) - 2.0*PI) < eps;//se quiser totalmente dentro tem que ver se ele ta na borda
}

void dfs(int u, int pai){
	//~ printf("estou em %d  pai = %d\n", u, pai);
	if(seen[u]){
		pts.clear();
		
		for(int i = len - 1; i >= 0; i--){
			pts.push_back(radar[pilha[i]].centro);
			//~ printf("%d ", i);
			if(pilha[i] == u) break;
		}
		//~ printf("\n");
		
		for(int i = 0; i < (int)informante.size(); i++){
			if(inside[i]) continue;
			inside[i] = insidePolygon(informante[i], pts);
		}
		
		return;
	}
	seen[u] = 1;
	pilha[len++] = u;
	
	for(int &v : g[u]){
		if(v != pai)
			dfs(v, u);
	}
	
	len--;
}

void removeInsideCycle(){
	buildGraph();
	memset(seen, 0, sizeof seen);
	memset(inside, false, sizeof inside);
	for (int i = 0; i < M; i++)
		if(!seen[i]){
			//~ printf("comecando dfs em %d\n", i);
			dfs(i, i);
		}
			
	informante.clear();
	for (int i = 0; i < N; i++)
		if(!inside[i])
			informante.push_back(copiaInformante[i]);
			
	N = (int)informante.size();

}

pair<ll, ll> minn(pair<ll, ll> a, pair<ll, ll> b){
	ll A = a.first, B = a.second;
	ll C = b.first, D = b.second;
	
	if(A * D < B * C) return a;
	return b;
}

bool maior(pair<ll, ll> a, pair<ll, ll> b){
	int A = a.first, B = a.second;
	int C = b.first, D = b.second;
	
	return A * D > B * C;
}

int solve(){
	int ans = -1;
	pair<ll, ll> aux = {0, 1};
	//~ printf("N = %d\n", N);
	for (int i = 0; i < N; i++)
	{
		//~ printf("i = %d\n", i);
		pair<ll, ll> tmp = {100000000, 1};
		for (int j = 0; j < B; j++)
		{
			pair<ll, ll> d = distPtSeg2(informante[i], country[j], country[(j + 1) % B]);
			tmp = minn(tmp, d);
		}
		
		//~ printf("tmp = %d / %d\n", tmp.first, tmp.second);
		if(maior(tmp, aux)){
			aux = tmp;
			ans = informante[i].id + 1;
		}
	}
	
	return ans;
}

void reset(){
	informante.clear();
	copiaInformante.clear();
	country.clear();
	radar.clear();
	chs.clear();
	int x = max({B, N, M});
	for (int i = 0; i < x; i++)
	{
		g[i].clear();
		seen[i] = 0;
	}
	len = 0;
}

int main(){
	int x, y, r;
	
	while(scanf("%d", &B) != EOF){
		reset();
		for (int i = 0; i < B; i++)
		{
			scanf("%d %d", &x, &y);
			country.push_back(pv(x, y));
		}
		
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			scanf("%d %d", &x, &y);
			copiaInformante.push_back(pv(x, y, i));
		}
		
		scanf("%d", &M);
		for (int i = 0; i < M; i++)
		{
			scanf("%d %d %d", &x, &y, &r);
			radar.push_back(circle(pv(x, y), r));
			//~ printf("Círculo((%d, %d), %d)\n", x, y, r);
		}
		
		if(!B && !N && !M) break;
		
		removeInsideRadar();
		removeInsideCycle();
		
		int ans = solve();
		if(ans == -1) printf("Mission impossible\n");
		else printf("Contact informer %d\n", ans);
	}
	
	return 0;
}
