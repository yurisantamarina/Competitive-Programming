#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
ll v[26];
string s;
map<ll, ll> mapa[26];

int main(){
	
	for (int i = 0; i < 26; i++)
	{
		cin >> v[i];
	}
	cin >> s;
	ll acc = 0;
	ll ans = 0;
	for (int i = 0; i < (int)s.size(); i++)
	{
		acc += v[s[i]-'a'];
		ans += mapa[s[i]-'a'][acc-v[s[i]-'a']];
		mapa[s[i]-'a'][acc]++;
	}
	cout << ans << "\n";
	
	
	return 0;
}
