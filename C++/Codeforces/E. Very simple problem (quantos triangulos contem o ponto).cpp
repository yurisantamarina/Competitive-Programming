#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 1000010
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
	ll operator ^ (pv other){
		return (ll)x * other.y - (ll)y * other.x;
	}
};

int n;
pv v[MAXN];
ll tot;

void update(int &j, int &sz, int val){
	j += val; sz += val;
	if(j == n + 1) j = 1;
	if(j == 0) j = n;
}

ll get(int sz){
	if(sz < 2) return 0;
	return ((ll)sz * (sz - 1)) / 2;
}

ll solve(pv p){
	int j = 2, sz = 2;
	ll fora = 0LL;
	
	v[n + 1] = v[1];
	bool entrou;
	for (int i = 1; i <= n; i++, sz--){
		if(i == j) update(j, sz, 1);
		
		while(((p - v[i]) ^ (v[j] - v[i])) > 0)
			update(j, sz, 1);
		
		//j ta um na frente (primeira posicao errada): -1 do j errado e -1 do i que ta fixo
		fora += get(sz - 2);
		
		if(((v[i] - p) ^ (v[i + 1] - p)) > 0)//fora do poligono
			return 0;
	}
	
	return tot - fora;
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &v[i].x, &v[i].y);
	
	tot = ((ll)n * (n - 1) * (n - 2)) / 6;
	
	
	int q, x, y;
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d %d", &x, &y);
		printf("%lld\n", solve(pv(x, y)));
	}
	
	
	return 0;
}
