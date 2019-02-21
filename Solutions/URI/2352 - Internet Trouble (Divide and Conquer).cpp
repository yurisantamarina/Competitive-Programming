#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define MAXN 6010
ll INF = 1000000000000000000LL;

ll v[MAXN];
ll sum[MAXN];
ll prod1[MAXN];
ll prod2[MAXN];
ll dp[2][MAXN];
ll N, B, C;
ll ANS;

void build(){
	sum[0] = 0LL;
	prod1[0] = 0LL;
	prod2[0] = 0LL;
	for (int i = 1; i <= N; i++)
	{
		sum[i] = sum[i-1] + v[i];
		prod1[i] = prod1[i-1] + v[i] * i;
		prod2[i] = prod2[i-1] + v[i] * (N - i + 1);
	}
}

ll getProd1(int l, int r){
	if(l > r) return 0LL;
	
	return prod1[r] - prod1[l-1];
}

ll getProd2(int l, int r){
	if(l > r) return 0LL;
	
	return prod2[r] - prod2[l-1];
}

ll getSum(int l, int r){
	if(l > r) return 0LL;
	return sum[r] - sum[l-1];
}

ll getFalta(int idx){
	return getProd1(idx+1, N) - getSum(idx+1, N) * (idx);
}



ll getCost(int l, int r){
	if(l > r) return 0LL;
	int mid = (l+r)/2;
	//~ printf("mid = %d cost(%d, %d) = %lld - %lld + %lld - %lld\n", mid, l, r, getProd1(l+1, mid), getSum(l+1, mid)*(l), getProd2(mid+1, r-1), getSum(mid+1, r-1)*(N-r));
	return getProd1(l+1, mid) - getSum(l+1, mid)*(l) + getProd2(mid+1, r-1) - getSum(mid+1, r-1)*(N - r + 1);
}

void calc(int k, int l, int r, int optL, int optR){
	if(l > r) return;
	int mid = (l+r)/2;
	int opt = 0;
	
	dp[k&1][mid] = INF;
	
	for (int i = max(optL, k-1); i < mid; i++)
	{
		if(i > optR) break;
		if(dp[(k-1)&1][i] + getCost(i, mid) * C + B < dp[k&1][mid]){
			dp[k&1][mid] = dp[(k-1)&1][i] + getCost(i, mid) * C + B;
			opt = i;
			//~ cout << "oi\n";
		}
	}
	
	ANS = min(ANS, dp[k&1][mid] + getFalta(mid) * C);
	calc(k, l, mid-1, optL, opt);
	calc(k, mid+1, r, opt, optR);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> B >> C;
	
	for (int i = 1; i <= N; i++)
	{
		cin >> v[i];
	}
	
	build();
	
	//~ cout << getCost(1, 6) << "\n";
	dp[1&1][0] = B;
	
	ANS = INF;
	
	for (int i = 1; i <= N; i++)
	{
		dp[1&1][i] = dp[1&1][i-1] + sum[i-1]*C;
		//~ cout << dp[1][i] << " ";
		ANS = min(ANS, dp[1&1][i] + getFalta(i) * C);
		//~ printf("getFalta(i) = %lld\n", getFalta(i));
	}
	//~ cout << endl;
	cout << ANS;
	for (int k = 2; k <= N; k++)
	{
		ANS = INF;
		calc(k, 1, N, 1, N);
		
		cout << " " << ANS;
	}
	
	//~ for (int i = 2; i <= N; i++)
	//~ {
		//~ for (int j = 1; j <= N; j++)
		//~ {
			//~ cout << dp[i][j] << " ";
		//~ }
		//~ cout << endl;
	//~ }
	
	cout << "\n";
	
	
	
	
	return 0;
}
