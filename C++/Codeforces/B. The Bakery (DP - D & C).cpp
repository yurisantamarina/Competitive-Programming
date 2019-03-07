#include <bits/stdc++.h>

using namespace std;
#define MAXN 35010

int cost = 0;
int v[MAXN], L, R, dp[51][MAXN], f[MAXN];

void add(int pos){
	int val = v[pos];
	f[val]++;
	if(f[val] == 1) cost++;
}

void del(int pos){
	int val = v[pos];
	f[val]--;
	if(f[val] == 0) cost--;
}

int arruma(int l, int r){
	while(L < l) del(L++);
	while(L > l) add(--L);
	while(R <= r) add(R++);
	while(R > r + 1) del(--R);
	
	return cost;
}

void calc(int k, int l, int r, int optL, int optR){
	if(l > r) return;
	int mid = (l+r)/2;
	int opt = 0, c;
	
	dp[k][mid] = 0;
	int lim = min(mid-1, optR);
	for(int i = optL; i <= lim; i++){
		c = arruma(i+1, mid);
		if(dp[k-1][i] + c > dp[k][mid]){
			dp[k][mid] = dp[k-1][i] + c;
			opt = i;
		}
	}
	calc(k, l, mid-1, optL, opt);
	calc(k, mid+1, r, opt, optR);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> v[i];
	
	L = 1;
	R = 1;
	for (int i = 1; i <= n; i++)
		dp[1][i] = arruma(1, i);
	
	for (int i = 2; i <= k; i++)
		calc(i, 1, n, 1, n);
	
	cout << dp[k][n] << "\n";
	
	return 0;
}
