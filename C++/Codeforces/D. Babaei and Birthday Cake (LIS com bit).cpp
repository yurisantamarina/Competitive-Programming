#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;

ll bit[MAXN], r[MAXN], h[MAXN], v[MAXN], dp[MAXN], n;
set<ll> s;
map<ll, int> mapa;

void update(int pos, ll val){
	for (int i = pos; i < MAXN; i += i & -i)
		bit[i] = max(bit[i], val);
}

ll query(int pos){
	ll ans = 0;
	for (int i = pos; i > 0; i -= i & -i)
		ans = max(ans, bit[i]);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> r[i] >> h[i];
		v[i] = r[i]*r[i]*h[i];
		s.insert(v[i]);
	}
	int idx = 2;
	ll ans = 0;
	for(auto i : s)
		mapa[i] = idx++;
	
	for (int i = 1; i <= n; i++)
	{
		dp[i] = query(mapa[v[i]] - 1) + v[i];
		update(mapa[v[i]], dp[i]);
		ans = max(ans, dp[i]);
	}
	cout << fixed << setprecision(10) << ans * acos(-1) << "\n";
	
	
	return 0;
}
