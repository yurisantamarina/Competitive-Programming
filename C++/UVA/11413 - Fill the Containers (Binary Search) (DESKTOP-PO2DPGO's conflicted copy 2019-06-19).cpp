#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const ll MOD = 0;
const ll N = 0;

ll n, k, mx;
ll v[100000];

bool ok(ll x){
	ll ki=1;
	ll sum=v[0];
	for (ll i = 1; i < n; i++)
	{
		if(sum + v[i] <= x){
			sum += v[i];
		}else{
			sum = v[i];
			ki++;
		}
	}
	return ki <= k;
}

int main () {
	while (cin >> n >> k)
	{
		mx = -1;
		for (ll i = 0; i < n; i++)
		{
			cin >> v[i];
			mx = max(mx, v[i]);
		}
		
		ll cnt=0;
		ll lo = mx, hi = 1000000000LL, mid;
		while (lo<=hi)
		{
			mid = (lo+hi)/2;
			if(ok(mid)) hi = mid-1;
			else lo = mid+1;
		}
		
		cout << lo << "\n";
	}
	
	
	
	
	
	return 0;
}
