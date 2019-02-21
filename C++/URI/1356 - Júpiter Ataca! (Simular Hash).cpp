#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
int B, MOD, n, q, v[MAXN], bit[MAXN];

int exp(int base, int e){
	if(e == 0) return 1;
	int aux = exp(base, e/2);
	aux = ((ll)aux * (ll)aux) % MOD;
	if(e & 1) aux = ((ll)aux * (ll)base) % MOD;
	return aux;
}

int inv(int a){
	return exp(a, MOD-2);
}

void update(int pos, int val){
	for (int i = pos; i < MAXN; i += i & -i){
		bit[i] += val;
		bit[i] %= MOD;
	}
}

int get(int pos){
	int ans = 0;
	for (int i = pos; i > 0; i -= i & -i){
		ans += bit[i];
		ans %= MOD;
	}
	return ans;
}

int query(int l, int r){
	return ((ll)get(r) - (ll)get(l-1) + 2LL*MOD) % MOD;
}

int main(){
	while(scanf("%d %d %d %d", &B, &MOD, &n, &q) != EOF){
		if(!B && !MOD && !n && !q) break;
		char op;
		int l, r, pos, val, h;
		for (int i = 0; i <= n+10; i++){
			v[i] = 0;
			bit[i] = 0;
		}
		
		for (int i = 0; i < q; i++)
		{
			scanf(" %c", &op);
			if(op == 'E'){
				scanf("%d %d", &pos, &val);
				update(pos, -((ll)v[pos]));
				v[pos] = ((ll)exp(B, n - pos) * (ll)val) % MOD;
				update(pos, v[pos]);
			}else{
				scanf("%d %d", &l, &r);
				h = ((ll)query(l, r) * (ll)inv(exp(B, n-r))) % MOD;
				printf("%d\n", h);
			}
		}
		printf("-\n");
	}
	
	
	
	return 0;
}
