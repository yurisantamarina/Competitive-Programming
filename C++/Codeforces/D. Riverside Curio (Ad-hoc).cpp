#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
ll n, v[MAXN], need[MAXN];

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> v[i];
		need[i] = v[i] + 1;
	}
	
	for (int i = n-1; i >= 1; i--)
		need[i] = max(need[i], need[i+1] - 1);
		
	ll ans = 0;
	for (int i = 2; i <= n; i++){
		need[i] = max(need[i], need[i-1]);
		ans += need[i] - v[i] - 1;
	}
	cout << ans << "\n";
	
	
	return 0;
}
