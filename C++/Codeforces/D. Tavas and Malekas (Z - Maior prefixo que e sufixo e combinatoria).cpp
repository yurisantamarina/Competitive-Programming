#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010100
typedef long long int ll;
ll m, n;
ll z[MAXN];
char seen[MAXN];
string s;
#define MOD 1000000007


void Z(){
	z[0] = 0;
	ll l = 0, r = 0;
	
	seen[0] = 1;
	for (ll i = 1; i < m; i++)
	{
		if(i <= r) z[i] = min(z[i - l], r - i +1);
		while(z[i] + i < m && s[z[i]] == s[z[i] + i]) z[i]++;
		if(i+z[i]-1 >= r){
			l = i;
			r = i+z[i]-1;
		}
		if(z[i] == m - i){
			seen[z[i]] = 1;
		}
	}
	
}

ll get(ll lst, ll at){
	lst = lst + m - 1;
	return max(0LL, lst - at + 1);
}

ll exp(ll base, ll e){
	if(e == 0) return 1;
	if(e == 1) return base;
	
	ll aux = exp(base, e/2);
	aux = (ll(aux) * ll(aux))%MOD;
	if(e%2 != 0) aux = (ll(aux) * ll(base))%MOD;
	return aux;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll k;
	cin >> n >> k;
	cin >> s;
	
	m = (ll)s.size();
	Z();
	
	
	ll at, lst, ans = k * m, overlap;
	for (ll i = 0; i < k; i++)
	{
		cin >> at;
		if(i){
			overlap = get(lst, at);
			ans -= overlap;
			if(!seen[overlap]){
				cout << "0\n";
				return 0;
			}
		}
		lst = at;
	}
	
	ans = exp(26, n - ans);
	
	cout << ans << "\n";
	
	
	return 0;
}
