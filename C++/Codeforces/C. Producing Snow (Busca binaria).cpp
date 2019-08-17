#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;

ll n, v[MAXN], acc[MAXN], inteiro[MAXN], parcial[MAXN], t[MAXN];

ll get(ll l, ll r){
	if(l > r) return 0;
	return acc[r] - acc[l-1];
}

void build(ll idx){
	
	ll lo = idx, hi = n, mid, ans = idx-1;
	
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(get(idx, mid) <= v[idx]){
			ans = max(ans, mid);
			lo = mid+1;
		}else hi = mid-1;
	}
	parcial[ans+1] += v[idx] - get(idx, ans);
	inteiro[idx]++;
	inteiro[ans+1]--;
}

int main(){
	cin >> n;
	for (ll i = 1; i <= n; i++)
		cin >> v[i];
	
	for (ll i = 1; i <= n; i++)
	{
		cin >> t[i];
		acc[i] = t[i] + acc[i-1];
	}
	
	for (ll i = 1; i <= n; i++)
		build(i);
	
	for (ll i = 1; i <= n; i++){
		inteiro[i] += inteiro[i-1];
		cout << inteiro[i] * t[i] + parcial[i] << " ";
	}

	cout << "\n";
	
	return 0;
}
