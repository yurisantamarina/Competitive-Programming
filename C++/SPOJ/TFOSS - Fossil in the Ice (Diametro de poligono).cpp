#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef long double ld;
#define MAXN 101010
#define F first
#define S second
typedef long long int ll;

struct pv{
	ll x, y;
	pv(){}
	pv(ll _x, ll _y){
		x = _x;
		y = _y;
	}
	ll operator ^ (pv other) const{// cross
		return x * other.y - y * other.x;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
	ll norma2(){//norma ao quadrado
		return x * x + y * y;
	}
	bool operator < (pv other) const{
		if(x == other.x) return y < other.y;
		return x < other.x;
	}
};

pv p[MAXN];
int n;


void ch(){
	sort(p, p + n);//ordena os pontos por x crescente, se empatar por y crescente
	pv p1[MAXN], p2[MAXN];
	
	int sz1 = 0, sz2 = 0;
	
	for (int i = 0; i < n; i++)
	{
		while(sz1 > 1 && ((p1[sz1-1] - p1[sz1 - 2]) ^ (p[i] - p1[sz1 - 2])) > 0)//aqui eu construo a hull de cima (> 0 pq se da 0 o cross quer dizer q estão colineares, então nao posso remover da pilha, consequentemente, eles ficam na convex hull)
			sz1--;
		p1[sz1++] = p[i];
		while(sz2 > 1 && ((p2[sz2-1] - p2[sz2 - 2]) ^ (p[i] - p2[sz2 - 2])) < 0)//aqui a de baixo
			sz2--;
		p2[sz2++] = p[i];
	}
	
	vector<pv> saida;
	
	n = 0;
	for (int i = 0; i < sz1; i++)
		p[n++] = p1[i];
	for (int i = sz2 - 2; i > 0; i--)
		p[n++] = p2[i];
	
	reverse(p, p + n);
}

//retorna a distancia ^ 2 do ponto 'c' à reta formada por 'a' e 'b'
ll dist2(pv a, pv b, pv c){
	ll area = abs((c - a) ^ (b - a));
	
	return area;
}

//retorna a distancia ^ 2 entre 'a' e 'b'
ll dist(pv a, pv b){
	ll A = (a.x - b.x);
	ll B = (a.y - b.y);
	return A * A + B * B;
}

ll diameter(){
	ll j = 1 % n, ans = 0;
	
	for (ll i = 0; i < n; i++)
	{
		while(dist2(p[i], p[(i + 1) % n], p[j]) < dist2(p[i], p[(i + 1) % n], p[(j + 1) % n]))
			j = ((j + 1) % n);
		
		ans = max({ans, dist(p[i], p[j]), dist(p[(i + 1) % n], p[j])});
	}
	
	return ans;
}

ll diameterBrute(){
	ll ans = 0;
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < n; j++)
			ans = max(ans, dist(p[i], p[j]));
	
	return ans;
}

ll diameterWrong(){
	ll j = 1 % n, ans = 0;
	
	for (ll i = 0; i < n; i++)
	{
		while(dist(p[i], p[j]) < dist(p[i], p[(j + 1) % n]))
			j = (j + 1) % n;
		
		ans = max({ans, dist(p[i], p[j])});
	}
	
	return ans; 
}

int main(){
	int tc;
	scanf("%d", &tc);
	while (tc--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lld %lld", &p[i].x, &p[i].y);
		
		ch();
		ll d = diameter();
		printf("%lld\n", d);
		//~ printf("O(n)   diametro ^ 2 = %lld\n", d);
		//~ printf("O(n)   diametro     = %.5lf\n", sqrt(d));
		
		//~ d = diameterBrute();
		//~ printf("\nO(n^2) diametro ^ 2 = %lld\n", d);
		//~ printf("O(n^2) diametro     = %.5lf\n", sqrt(d));
		
		//~ d = diameterWrong();
		//~ printf("\nO(n)   diametro ^ 2 = %lld\n", d);
		//~ printf("O(n)   diametro     = %.5lf\n", sqrt(d));
	}
	
	
	
	return 0;
}
