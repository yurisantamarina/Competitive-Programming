#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define MAXN 300110
#define pb push_back

ll n;
ll v[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	sort(v, v+n);
	
	ll ans = 0LL;
	for (int i = 0; i < n; i++)
	{
		ans += abs(v[i] - (i + 1));
	}
	cout << ans << "\n";
	
	return 0;
}
