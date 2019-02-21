#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define MOD 1000000007

typedef long long int ll;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	
	ll operator ^ (pv other){
		return (ll)x * other.y - (ll)y * other.x;
	}
	
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
};

int fat[MAXN], n, k;
pv v[MAXN];

int exp(int base, int e){
	if(e == 0) return 1;
	int aux = exp(base, e / 2);
	aux = ((ll)aux * aux) % MOD;
	if(e & 1) aux = ((ll)aux * base) % MOD;
	return aux;
}

int inv(int a){
	return exp(a, MOD - 2);
}

int comb(int N, int K){
	if(K > N) return 0;
	int num = fat[N];
	int den = ((ll)fat[K] * fat[N - K]) % MOD;
	den = inv(den);
	
	return ((ll)num * den) % MOD;
}

void build(){
	fat[0] = 1;
	for (int i = 1; i < MAXN; i++)
		fat[i] = ((ll)fat[i - 1] * i) % MOD;
}

int solve(pv p){
	int j = 1, len = 2;
	int fora = 0;
	for (int i = 0; i < n; i++)
	{
		while(((v[(j + 1) % n] - v[i]) ^ (p - v[i])) >= 0){
			j = (j + 1) % n;
			len++;
		}
		
		fora = (fora + comb(len - 1, k - 1)) % MOD;
		len--;
	}
	
	
	return fora;
}

int main(){
	build();
	int x, y;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &v[i].x, &v[i].y);
	
	scanf("%d %d", &x, &y);
	
	int ans = ((ll)comb(n, k) - (ll)solve(pv(x, y)) + 2LL * MOD) % MOD;
	printf("%d\n", ans);
	
	return 0;
}
