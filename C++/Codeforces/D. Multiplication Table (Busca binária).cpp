#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

ll n, m;
ll get(ll mid){
	ll ans = 0LL;
	for (ll i = 1LL; i <= min(mid, n); i++)
	{
		ans += min(mid/i, m);
	}
	return ans;
}

int main(){
	ll k, aux;
	cin >> n >> m >> k;
	
	ll lo = 1LL, hi = n * m, mid;
	while (lo <= hi)
	{
		mid = (lo + hi)/2LL;
		aux = get(mid);
		if(aux == k){
			hi = mid-1;
		}else if(aux > k) hi = mid-1;
		else lo = mid+1;
	}
	cout << lo << "\n";
	
	
	
	return 0;
}
