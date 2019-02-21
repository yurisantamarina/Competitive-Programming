#include <bits/stdc++.h>

using namespace std;
#define MAXN 5010
#define mp make_pair
#define MOD 1000000007	
int n, a, b, k;
pair<int, int> limite[MAXN];
int dp[MAXN][MAXN];
int acc[MAXN];

bool atinge(int j, int i){
	return abs(j - b) > abs(j - i);
}

void preprocessa(int l, int r){
	int mn, mx;
	for (int i = l; i <= r; i++)
	{
		mn = i; mx = i;
		for (int j = l; j <= r; j++)
		{
			if(i==j) continue;
			if(atinge(j, i)){
				mn = min(mn, j);
				mx = max(mx, j);
			}
		}
		limite[i] = mp(mn, mx);
	}
}

int get(int l, int r){
	return (acc[r] - acc[l-1] + MOD)%MOD;
}

int getSomatorio(int andar){
	int l = limite[andar].first;
	int r = limite[andar].second;
	
	return (get(l, r) - get(andar, andar) + MOD)%MOD;
}

void build(int lvl, int l, int r){
	acc[0] = 0;
	for (int i = l; i <= r; i++)
	{
		acc[i] = (acc[i-1] + dp[i][lvl])%MOD;
	}
}

int main(){
	scanf("%d %d %d %d", &n, &a, &b, &k);
	
	int l, r;
	if(a < b){
		l = 1; 
		r = b-1;
	}else{
		l = b+1;
		r = n;
	}
	preprocessa(l, r);
	
	int ans = 0;
	dp[a][0] = 1;
	build(0, l, r);
	for (int qtd = 1; qtd <= k; qtd++)
	{
		for (int andar = l; andar <= r; andar++)
		{
			dp[andar][qtd] = getSomatorio(andar);
			
			if(qtd == k) ans = (ans + dp[andar][qtd])%MOD;
		}
		build(qtd, l, r);
	}
	printf("%d\n", ans);
	
	return 0;
}
