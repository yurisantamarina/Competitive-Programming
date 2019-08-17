#include <bits/stdc++.h>

using namespace std;
#define MAXN 5010

int z[MAXN][MAXN];
int mx[MAXN][MAXN];
int dp[MAXN];
int n, a, b;
string s;

void calc(int beg){
	z[beg][beg] = 0;
	int l = beg, r = beg;
	
	for (int i = beg + 1; i < n; i++){
		if(i <= r)
			z[beg][i] = min(z[beg][i - l + beg], r - i + 1);
		while(i + z[beg][i] < n && s[z[beg][i] + beg] == s[i + z[beg][i]])
			z[beg][i]++;
		if(i + z[beg][i] - 1 > r){
			l = i;
			r = i + z[beg][i] - 1;
		}
		mx[i][beg] = z[beg][i];
		if(beg > 0)
			mx[i][beg] = max(mx[i][beg], mx[i][beg - 1]);
	}
}

bool ok(int l, int r){
	int sz = r - l + 1;
	if(l - sz < 0) return false;
	return mx[l][l - sz] >= sz;
}

int solve(){
	dp[0] = a;
	for(int i = 1; i < n; i++){
		dp[i] = dp[i - 1] + a;
		for(int j = 0; j <= i; j++){
			if(ok(j, i))
				dp[i] = min(dp[i], dp[j - 1] + b);
		}
	}
	return dp[n - 1];
}

int main(){
	cin >> n >> a >> b >> s;
	for (int i = 0; i < n; i++){
		calc(i);
	}
	cout << solve() << "\n";
	
	return 0;
}
