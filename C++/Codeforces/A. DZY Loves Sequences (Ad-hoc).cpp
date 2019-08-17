#include <bits/stdc++.h>

using namespace std;
#define MAXN 100010
int n, v[MAXN], pref[MAXN], suf[MAXN];

void build(){
	
	for (int i = 1, j = n; i <= n; i++, j--)
	{
		if(v[i] > v[i-1]) pref[i] = pref[i-1] + 1;
		else pref[i] = 1;
		
		if(v[j] < v[j+1]) suf[j] = suf[j+1] + 1;
		else suf[j] = 1;
	}
	
}

int main(){
	cin >> n;
	
	v[0] = -1;
	v[n+1] = 1000000010;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
	}
	build();
	
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if(v[i+1] - v[i-1] >= 2){
			ans = max(ans, pref[i-1] + 1 + suf[i+1]);
		}
		ans = max(ans, pref[i-1] + 1);
		ans = max(ans, suf[i+1] + 1);
	}
	cout << ans << "\n";
	
	return 0;
}
