#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 19
ll n, l, r, x, c[MAXN];

int main(){
	
	cin >> n >> l >> r >> x;
	for (int i = 0; i < n; i++)
		cin >> c[i];
	
	ll ans = 0LL;
	for (int i = 0; i < 1<<n; i++)
	{
		ll mx = 0, mn = 1000000000000000LL, sum = 0LL;
		for (int j = 0; j < n; j++)
		{
			if(i & (1 << j)){
				mx = max(mx, c[j]);
				mn = min(mn, c[j]);
				sum += c[j];
			}
		}
		if(sum >= l && sum <= r && mx - mn >= x)
			ans++;
	}
	cout << ans << "\n";
	
	return 0;
}
