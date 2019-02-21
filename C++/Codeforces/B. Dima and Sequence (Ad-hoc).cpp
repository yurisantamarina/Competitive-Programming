#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
map<int, int> memo;
int cnt[100];

int f(int x){
	if(x == 0) return 0;
	if(memo.count(x)) return memo[x];
	return memo[x] = f(x/2) + x%2;
}

int main(){
	int n, x;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		cnt[f(x)]++;
	}
	
	ll ans = 0LL;
	for (int i = 0; i < 70; i++)
	{
		if(cnt[i] == 0) continue;
		ans += ((ll)cnt[i] * (cnt[i]-1));
	}
	ans /= 2;
	cout << ans << "\n";
	
	return 0;
}
