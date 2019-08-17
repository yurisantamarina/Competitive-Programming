#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define MAXN 1000000
#define mp make_pair
#define pb push_back

int seq[5][1010];
int edge[5][1010][1010];
int n, k;
int dp[1010];

void build(int idx){
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			edge[idx][seq[idx][i]][seq[idx][j]] = 1;
		}
	}
}

bool pode(int i, int j){
	for(int idx = 1; idx < k; idx++){
		if(!edge[idx][seq[0][i]][seq[0][j]]){
			return false;
		}
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> seq[i][j];
		}
	}
	for (int i = 0; i < k; i++)
	{
		build(i);
	}
	
	int ans = 0, mx = 0;
	for (int i = 0; i < n; i++)
	{
		ans = 1;
		for (int j = 0; j < i; j++)
		{
			if(pode(i, j)) ans = max(ans, 1 + dp[j]);
		}
		dp[i] = ans;
		mx = max(mx, ans);
	}
	
	cout << mx << "\n";
	
	
	
	
	
	
	return 0;
}
