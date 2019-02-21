#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

ll MOD = 1000000007LL, N, K;

ll exp(ll base, ll e){
	if(e == 0) return 1LL;
	ll aux = exp(base, e / 2LL);
	aux = (aux * aux) % MOD;
	if(e & 1) aux = (aux * base) % MOD;
	return aux;
}

ll inv(ll a){
	return exp(a, MOD - 2LL);
}

ll getQtd(ll X, ll mn, ll mx){
	ll num = 1;
	
	for(ll i = X; i > mx; i--)
		num = (num * i) % MOD;
	
	ll den = 1;
	for(ll i = 1; i <= mn; i++)
		den = (den * i) % MOD;
	return (num * inv(den)) % MOD;
}

ll sobra(ll pedacos){
	ll s = N - (pedacos - 1) - K;
	ll mn = pedacos;
	ll mx = s;
	if(mn > mx) swap(mn, mx);
	return getQtd(pedacos + s, mn, mx);
}

ll grupo(ll pedacos){
	ll mn, mx;
	mn = pedacos - 1;
	mx = (K - 1) - (pedacos - 1);
	if(mn > mx) swap(mn, mx);
	return getQtd(K - 1, mn, mx);
}

int main(){
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%lld %lld", &N, &K);
		
		ll ans = 0LL;
		for(ll pedacos = 1; pedacos <= K; pedacos++){
			if(K + pedacos - 1 > N) break;
			ans = (ans + (((grupo(pedacos) * sobra(pedacos)) % MOD) * exp(2, pedacos)) % MOD) % MOD;
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
	
