#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long int ll;
#define eps 1e-10

struct pv{
	ll x, y;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
	ll operator ^ (pv other) const{
		return (ll)x * other.y - (ll)y * other.x;
	}
};

struct reta{
	pv p0, v;
	reta(){}
	reta(pv a, pv b){
		p0 = a;
		v = b;
	}
};

ll ans[1010101], n, m;
vector<pv> v;


ll getX(reta r){
	//~ long double t = (-1.0 * r.p0.y) / r.v.y;
	ll num = r.p0.x * r.v.y - r.p0.y * r.v.x;
	ll den = r.v.y;
	
	if(num % den == 0) return num / den;
	
	return -1;
}

void update(ll i, ll j){
	ll hol = getX(reta(v[i], v[j] - v[i]));
	if(hol < 1 || hol > n) return;
	ll cnt = 2;
	for (ll k = 0; k < m; k++)
		if(i != k && j != k && ((v[j] - v[i])^(v[k] - v[i])) == 0)
			cnt++;
	
	ans[hol] = max(ans[hol], cnt);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll x, y;
	cin >> n >> m;
	for (ll i = 0; i < m; i++)
	{
		cin >> x >> y;
		v.pb(pv(x, y));
	}
	for (ll i = 0; i < m; i++)
		for (ll j = 0; j < m; j++)
			if(v[i].y != v[j].y)
				update(i, j);
	
	ll sum = 0;		
	for (ll i = 1; i <= n; i++)
		sum += max(ans[i], 1LL);
	
	cout << sum << "\n";

	return 0;
}
