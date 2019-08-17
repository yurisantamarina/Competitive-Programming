#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 200010
ll inf = 1000000000000000LL;

ll n, k;
ll v[MAXN];
ll acc[MAXN];
ll sum[MAXN];
pair<ll, ll> mx[MAXN];

pair<ll, ll> _max(pair<ll, ll> a, pair<ll, ll> b){
	if(a.F >= b.F) return a;
	return b;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for (ll i = 1; i <= n; i++)
	{
		cin >> v[i];
		acc[i] = acc[i-1] + v[i];
	}
	for (ll i = 1; i <= n; i++)
	{
		if(i + k - 1 > n) sum[i] = -inf;
		else sum[i] = acc[i + k - 1] - acc[i-1];
	}
	
	mx[n] = mp(sum[n], n);
	for (ll i = n-1; i >= 1; i--)
	{
		mx[i] = _max(mp(sum[i], i), mx[i+1]);
	}
	
	ll ans = 0LL;
	ll a=inf, b=inf;
	for (ll i = 1; i <= n; i++)
	{
		if(i + k > n) break;
		if(sum[i] + mx[i+k].F > ans){
			ans = sum[i] + mx[i+k].F;
			a = i;
			b = mx[i+k].S;
		}
	}
	cout << a << " " << b << "\n";
	
	
	
	return 0;
}
