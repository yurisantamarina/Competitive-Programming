#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, d, m, v[200], ans = 0;
	cin >> n >> d;
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	cin >> m;
	sort(v, v+n);
	for (int i = 0; m && i < n; i++)
	{
		m--;
		ans += v[i];
	}
	
	ans -= m * d;
	cout << ans << "\n";
	
	
	
	return 0;
}
