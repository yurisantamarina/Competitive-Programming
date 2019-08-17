#include <bits/stdc++.h>

using namespace std;
#define MAXN 8010
string s;
int p[MAXN][MAXN];
int dp[MAXN];

void kmp(int pos){
	p[pos][pos] = pos;
	for (int i = pos+1; i < s.size(); i++)
	{
		p[pos][i] = p[pos][i-1];
		while(s[p[pos][i]] != s[i] && p[pos][i] > pos) p[pos][i] = p[pos][p[pos][i] - 1];
		if(s[p[pos][i]] == s[i]) p[pos][i]++;
	}
}

int qtdDig(int n){
	if(n < 10) return 1;
	if(n < 100) return 2;
	if(n < 1000) return 3;
	return 4;
}

int getCost(int i, int j){
	int prefixF = max(p[j][i]-j, 0);
	int pos = i-j+1;
	
	if(pos % (pos - prefixF) == 0){
		int periodo = pos / (pos - prefixF);
		int qtdLetras = pos / periodo;
		return qtdDig(periodo)+qtdLetras;
	}
	return 1 + pos;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> s;
	for (int i = 0; i < s.size(); i++)
		kmp(i);
	
	int n = s.size();
	dp[0] = 2;//1a
	
	for (int i = 1; i < n; i++)
	{
		dp[i] = 1e9;
		for (int j = 0; j <= i; j++)
			dp[i] = min(dp[i], (j-1<0 ? 0 : dp[j-1]) + getCost(i, j));
	}
	cout << dp[n-1] << "\n";
	
	
	return 0;
}
