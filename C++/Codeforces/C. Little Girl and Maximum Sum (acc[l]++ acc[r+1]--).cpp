#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define pb push_back

int acc[200010];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q, x, l, r;
	vector<ll> v, v2;
	
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		v.pb(x);
	}
	
	sort(v.rbegin(), v.rend());
	
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		acc[l]++;
		acc[r+1]--;
	}
	
	for (int i = 1; i <= n; i++)
	{
		acc[i] += acc[i-1];
		v2.pb(acc[i]);
	}
	
	sort(v2.rbegin(), v2.rend());
	
	ll sum = 0LL;
	for (int i = 0; i < n; i++)
	{
		sum += v[i] * v2[i];
	}
	cout << sum << "\n";
	
	
	
	
	return 0;
}
