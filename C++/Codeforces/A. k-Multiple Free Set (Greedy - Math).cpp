#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

unordered_set<ll> forb;
ll v[101010], n, k;

int main(){
	cin >> n >> k;
	
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	sort(v, v+n);
	
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if(!forb.count(v[i])){
			ans++;
			forb.insert(v[i] * k);
		}
	}
	cout << ans << "\n";
	
	
	return 0;
}
