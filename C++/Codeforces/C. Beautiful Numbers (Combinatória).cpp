#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MOD 1000000007
#define MAXN 1000010

ll a, b, n;
ll fat[MAXN];

ll add(ll x, ll y){
	return (x + y)%MOD;
}

ll poww(ll base, ll exp){
	if(exp == 0LL) return 1LL;
	ll aux = poww(base, exp/2LL);
	aux = (aux * aux)%MOD;
	if(exp%2 != 0) aux = (aux * base)%MOD;
	return aux;
}

ll inversoModular(ll x){
	return poww(x, MOD-2LL);
}

ll comb(ll N, ll K){
	return (fat[N] * inversoModular((fat[N-K] * fat[K])%MOD))%MOD;
}

void build(){
	
	fat[0] = 1LL;
	for (ll i = 1LL; i < MAXN; i++)
	{
		fat[i] = fat[i-1] * i;
		fat[i] %= MOD;
	}
		
}

bool ok(ll val){
	
	ll lst;
	while (val > 0)
	{
		lst = val % 10;
		if(lst != a && lst != b) return false;
		val /= 10LL;
	}
	
	return true;
}

int main(){
	cin >> a >> b >> n;
	
	build();
	
	ll num, ans = 0LL;
	for (ll qtdA = 0, qtdB = n; qtdA <= n; qtdA++, qtdB--)
	{
		num = a * qtdA + b * qtdB;
		if(ok(num))
			ans = add(ans, comb(n, qtdA));
	}
	cout << ans << "\n";
	
	
	
	r
