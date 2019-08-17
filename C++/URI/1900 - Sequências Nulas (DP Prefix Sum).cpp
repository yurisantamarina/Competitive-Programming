#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi prllf("oioi\n")
#define digitCountDec(a) (ll)floor(1 + log10((double)a))
#define digitCount(a, b) (ll)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
ll v[100010];
ll a[100010];
map<ll, ll> mapa;

ll func(ll n){
	return ((1+n)*n)/2.0;
}

int main () {
	ll n;
	cin >> n;
	a[0] = 0LL;
	mapa[0]++;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		a[i] = a[i-1]+v[i];
		mapa[a[i]]++;
	}
	
	//~ for (int i = 0; i <= n; i++)
	//~ {
		//~ cout << a[i] << " ";
	//~ }
	//~ cout << endl;
	
	
	ll ans=0LL;
	for(auto i : mapa){
		ans += func(i.S - 1);
	}
	cout << ans << endl;
	
	
	return 0;
}
