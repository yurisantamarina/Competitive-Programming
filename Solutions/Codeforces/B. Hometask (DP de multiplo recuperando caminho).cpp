#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define MAXN 1000010

int dp[MAXN][30];
char memo[MAXN][30];
int n;
int s[MAXN];

int solve(int pos, int mod){
	if(pos == n) return mod == 0 ? 0 : -1e9;
	if(memo[pos][mod]) return dp[pos][mod];
	memo[pos][mod] = 1;
	
	int ans = 0;
	ans = max(solve(pos+1, mod), 1 + solve(pos+1, (mod*10 + s[pos])%30));
	
	return dp[pos][mod] = ans;
}

string saida="";
void path(int pos, int mod){
	if(pos == n) return;
	
	if(dp[pos][mod] == 1 + solve(pos+1, (mod*10 + s[pos])%30)){
		saida += (s[pos]+'0');
		path(pos+1, (mod*10 + s[pos])%30);
	}else{
		path(pos+1, mod);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	sort(s, s+n);
	reverse(s, s+n);
	
	int aux = solve(0, 0);
	
	if(aux == 0) cout << "-1\n";
	else{
		path(0, 0);
		if(saida[0] == '0') cout << "0\n";
		else cout << saida << "\n";
		
	}
	
	
	return 0;
}
