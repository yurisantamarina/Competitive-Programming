#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

ll lcm(ll a, ll b){
	return a*b / __gcd(a, b);
}

ll n, l, v[101010], gc, lc;

int main(){
	cin >> n >> l;
	ll mx;
	for (ll i = 0; i < n; i++)
	{
		cin >> v[i];
		if(i == 0){
			lc = v[i];
		}else{
			lc = lcm(v[i], lc);
		}
		mx = max(mx, v[i]);
	}
	//~ cout << gc << " " << lc << endl;
	//~ cout << lc << endl;
	
	ll mx2, nwgc, nwlc, ans = 0, val;
	for (ll i = 1; i <= 100000; i++)
	{
		nwlc = lcm(lc, i);
		mx2 = max(mx, i);
		
		//~ prllf("testando %d  nwgc = %d  nwlc = %d  mx2 = %d\n", i, nwgc, nwlc, mx2);
		if(nwlc <= l){
			if(nwlc > ans){
				ans = nwlc;
				val = i;
			}
		}
	}
	cout << val << "\n";
	
	return 0;
}
