#include <bits/stdc++.h>

using namespace std;
#define MOD 1000000007
#define MAXN 101010
typedef long long int ll;

ll a[MAXN], b[MAXN], n, m;
ll dp[MAXN];
char memo[MAXN];
int acc[MAXN];

ll exp(ll base, ll e){
	if(e == 1) return base;
	if(e == 0) return 1;
	
	ll aux = exp(base, e / 2);
	aux = (aux * aux) % MOD;
	if(e & 1) aux = (aux * base) % MOD;
	
	return aux;
}

ll get(int l, int r){
	if(l > r) return 1LL;
	int qtd = acc[r] - (l ? acc[l - 1] : 0);
	return exp(m, qtd);
}

ll solve(int pos){
	if(pos == n) return 0LL;
	if(memo[pos]) return dp[pos];
	ll &ans = dp[pos];
	
	if(a[pos] && b[pos]){
		if(a[pos] > b[pos]) return ans = 1 * get(pos + 1, n-1);
		if(a[pos] < b[pos]) return ans = 0;
		return ans = solve(pos + 1);
	}
	
	if(a[pos] && !b[pos])
		return ans = (1 * solve(pos + 1) + ((a[pos] - 1) * get(pos + 1, n-1)) % MOD) % MOD;
	
	if(!a[pos] && b[pos])
		return ans = (1 * solve(pos + 1) + ((m - b[pos]) * get(pos + 1, n-1)) % MOD) % MOD;
	
	//a[i] == 0 && b[i] == 0
	return ans = ((m * solve(pos + 1))%MOD + ((((m * (m - 1)) / 2) % MOD) * get(pos + 1, n-1)) % MOD) % MOD;
}

int main(){
	ll qtd0 = 0LL;
	ll qtd1 = 0LL;
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	
	for (int i = 0; i < n; i++){
		cin >> b[i];
		acc[i] = (b[i] == 0) + (a[i] == 0);
		if(i) acc[i] += acc[i-1];
		
		//~ cout << acc[i] << " ";
	}
	//~ cout << endl;
	
	qtd0 = acc[n-1];
	//~ cout << "qtd0 = " << qtd0 << endl;
	ll num = solve(0);
	//~ cout << "num = " << num << endl;
	ll den = exp(m, qtd0);
	//~ cout << "den = " << den << endl;
	//~ ll g = __gcd(num, den);
	//~ num /= g;
	//~ den /= g;
	den = exp(den, MOD - 2);
	
	cout << (num * den) % MOD << "\n";
	
	return 0;
}
