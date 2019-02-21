#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
int v[MAXN];
int ans[MAXN];
int n;

int solve(int idx){
	int lo = idx+1, hi = n-1, mid, ans = -1;
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(v[mid] >= v[idx]){
			hi = mid-1;
		}else{
			lo = mid+1;
			ans = max(ans, mid);
		}
	}
	return ans == -1 ? ans : ans - idx - 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	for (int i = n-2; i >= 0; i--)
	{
		ans[i] = solve(i);
		v[i] = min(v[i], v[i+1]);
	}
	ans[n-1] = -1;
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << " ";
	}
	cout << "\n";
	
	
	
	return 0;
}
