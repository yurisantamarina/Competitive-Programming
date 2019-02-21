#include <bits/stdc++.h>

using namespace std;
#define MAXN 501010
#define INF 2000000000000000000LL
#define F first
#define S second
#define mp make_pair
typedef long long int ll;

ll add[MAXN], v[MAXN], acc[MAXN], def[MAXN];
ll n, r, k;

bool ok(ll resp){
	ll L = 1, R = 1, falta = k, mn = INF;
	
	memset(acc, 0, sizeof acc);
	memset(add, 0, sizeof add);
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << def[i+1] << " ";
	//~ }
	//~ cout << endl;	
	
	ll pos, x;
	for (ll i = 1; i <= n; i++)
	{
		add[i] += add[i-1];
		acc[i] = def[i] + add[i];
		
		if(acc[i] < resp){
			pos = min(i+r, n);
			x = min(falta, resp - acc[i]);
			add[max(i, pos - r)] += x;
			add[min(n+1, pos + r + 1)] -= x;
			
			acc[i] += x;
			falta -= x;
			//~ cout << i << " esta abaixo\n";
		}
		mn = min(mn, acc[i]);
		//~ cout << acc[i] << " ";
	}
	//~ cout << endl;
	
	
	return mn >= resp;
}

ll solve(){
	ll lo = 0, hi = INF, mid, ans = -INF;
	//~ ok(15);
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(ok(mid)){
			ans = max(ans, mid);
			lo = mid+1;
		}else hi = mid-1;
	}
	
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> r >> k;
	for (ll i = 1; i <= n; i++)
	{
		cin >> v[i];
		def[max(1LL, i - r)] += v[i];
		def[min(n+1, i + r + 1)] -= v[i];
	}
	for (ll i = 1; i <= n; i++)
		def[i] += def[i-1];
	
	cout << solve() << "\n";
	
	return 0;
}
