#include <bits/stdc++.h>

using namespace std;
#define MAXN 1000100

typedef long long int ll;

int v[MAXN];
map<int, int> mapa;
ll bit[MAXN];
ll dp[MAXN][4];

ll query(int please){
	ll ans = 0LL;
	for(please; please > 0; please -= please & -please){
		ans += bit[please];
	}
	return ans;
}

void update(int please, ll val){
	for (please; please < MAXN; please += please & -please)
	{
		bit[please] += val;
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	set<int, greater<int> > s;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		s.insert(v[i]);
	}
	int idx = 2;
	for(auto i : s){
		mapa[i] = idx++;
	}
	
	for (int i = 0; i < n; i++)
	{
		v[i] = mapa[v[i]];
		dp[i][1] = 1;
	}
	
	ll ans = 0LL;
	for (int k = 2; k <= 3; k++)
	{
		memset(bit, 0, sizeof bit);
		for (int i = 0; i < n; i++)
		{
			dp[i][k] = query(v[i]-1);
			update(v[i], dp[i][k-1]);
			
			if(k == 3) ans += dp[i][k];
		}
		
	}
	
	cout << ans << "\n";
	
	
	
	
	
	return 0;
}
