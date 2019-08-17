#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001
#define BLOCK 500
typedef long long int ll;
#define gc getchar // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

struct bit{
	int t[MAXN];
	bit(){
		//~ memset(t, 0, sizeof t);
	}
	
	void update(int pos, int val){
		for (pos; pos < MAXN; pos += pos & -pos)
			t[pos] += val;
	}
	
	int sum(int pos){
		int ans = 0;
		for (pos; pos > 0; pos -= pos & -pos)
			ans += t[pos];
		return ans;
	}
	
	int query(int l, int r){
		if(l > r) return 0;
		return sum(r) - sum(l-1);
	}
};

bit bloco[BLOCK];
int v[MAXN];
int n;

int ini(int b){
	return b * BLOCK + 1;
}

int fim(int b){
	return min(ini(b+1)-1, n);
}

int query(int l, int r, int val){
	int bl = (l-1) / BLOCK;
	int br = (r-1) / BLOCK;
	
	int INI, FIM, ans = 0;
	INI = ini(bl);
	FIM = fim(bl);
	for (int i = INI; i <= FIM; i++)
		if(i >= l && i <= r) 
			ans += (v[i] < val);
	if(bl == br) return ans;
	
	INI = ini(br);
	FIM = fim(br);
	for (int i = INI; i <= FIM; i++)
		if(i >= l && i <= r) 
			ans += (v[i] < val);
			
	for (int i = bl+1; i < br; i++)
		ans += bloco[i].query(1, val-1);
	
	return ans;
}

void update(int idx, int op){
	bloco[(idx-1) / BLOCK].update(v[idx], op);
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int q;
	scanint(n);
	scanint(q);
	for (int i = 1; i <= n; i++)
	{
		bloco[(i-1) / BLOCK].update(i, 1);
		v[i] = i;
	}
	
	ll at = 0LL;
	int menorQL, maiorQR, menorQL2, maiorQR2, inv1, inv2, l, r;
	for (int i = 0; i < q; i++)
	{
		scanint(l);
		scanint(r);
		if(l == r){
			printf("%lld\n", at);
			continue;
		}
		if(l > r) swap(l, r);
		menorQL = query(l+1, r-1, v[l]);
		maiorQR = ((r-1) - (l+1) + 1) - query(l+1, r-1, v[r]);
		
		if(v[l] < v[r]){
			inv1 = 0;
			inv2 = 1;
		}else{
			inv1 = 1;
			inv2 = 0;
		}
		
		update(l, -1);
		update(r, -1);
		swap(v[l], v[r]);
		update(l, 1);
		update(r, 1);
		
		menorQL2 = query(l+1, r-1, v[l]);
		maiorQR2 = ((r-1) - (l+1) + 1) - query(l+1, r-1, v[r]);
		
		at = at - menorQL - maiorQR - inv1 + menorQL2 + maiorQR2 + inv2;
		printf("%lld\n", at);
	}
	
	
	
	
	
	return 0;
}
