#include <bits/stdc++.h>

using namespace std;
#define MAXN 5010

int v[MAXN], n, q, acc[MAXN], l[MAXN], r[MAXN];

int get(int a, int b){
	return acc[b] - acc[a - 1];
}

int solve(int at){
	for(int i = l[at]; i <= r[at]; i++){
		v[i]--;
	}
	
	int covered = 0, ans = 0;
	
	for(int i = 1; i <= n; i++){
		if(v[i] > 0)
			covered++;
		if(v[i] == 1)
			acc[i] = 1;
		else
			acc[i] = 0;
			
		acc[i] += acc[i - 1];
	}
	
	for(int i = 1; i <= q; i++){
		if(i == at)
			continue;
		ans = max(ans, covered - get(l[i], r[i]));
	}
	
	for(int i = l[at]; i <= r[at]; i++){
		v[i]++;
	}
	
	return ans;
}

int main(){
	cin >> n >> q;
	for (int i = 1; i <= q; i++){
		cin >> l[i] >> r[i];
		for(int j = l[i]; j <= r[i]; j++){
			v[j]++;
		}
	}
	
	int ans = 0;
	for(int i = 1; i <= q; i++){
		ans = max(ans, solve(i));
	}
	cout << ans << "\n";
	
	return 0;
}
