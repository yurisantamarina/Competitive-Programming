#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

ll dp[(1<<18)+10][102];
string n;
int m, sz;
ll fat[19];
ll pot[19];
int cnt[10];

void build(){
	
	fat[0] = 1LL;
	pot[0] = 1LL;
	for (int i = 1; i < sz; i++)
	{
		fat[i] = fat[i-1]*ll(i);
		pot[i] = pot[i-1]*ll(10);
	}
	fat[sz] = fat[sz-1]*ll(sz);
	pot[sz] = pot[sz-1]*ll(10);
	
}


ll solve(){
	for (int i = 0; i < sz; i++)
	{
		cnt[n[i] - '0']++;
		if(n[i] == '0') dp[1 << i][(pot[sz-1] * (n[i] - '0')) % m] = 0;
		else dp[1 << i][(pot[sz-1] * (n[i] - '0')) % m] = 1;
	}
	
	int i, nmod, atv;
	for (int mask = 1; mask < 1<<sz; mask++)
	{
		atv = __builtin_popcount(mask);
		if(atv <= 1) continue;
		
		for (int mod = 0; mod < m; mod++)
		{
			dp[mask][mod] = 0;
			for (int aux = mask; aux > 0; aux -= aux & -aux)
			{
				i = __builtin_ctz(aux & -aux);
				nmod = (mod - (pot[sz - atv] * (n[i] - '0'))%m);
				while (nmod < 0) nmod += m;
				while (nmod >= m) nmod -= m;
				
				dp[mask][mod] += dp[mask ^ (1 << i)][nmod];
			}
		}
	}
	
	
	ll aux = 1LL;
	for (int i = 0; i < 10; i++)
	{
		aux *= fat[cnt[i]];
	}
	
	return dp[(1<<sz)-1][0] / aux;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	sz = (int)n.size();
	build();
	
	cout << solve() << "\n";
	
	
	return 0;
}
