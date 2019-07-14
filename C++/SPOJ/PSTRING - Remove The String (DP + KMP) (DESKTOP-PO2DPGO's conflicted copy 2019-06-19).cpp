#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define INF 1e9

string s, t;
int p[MAXN];
int dp[10100][1010];
char memo[10100][1010];
int dp2[10100][1010];
char memo2[10100][1010];


void build(){
	int idx;
	p[0] = 0;
	for (int i = 1; i < (int)t.size(); i++)
	{
		idx = p[i-1];
		while(t[idx] != t[i] && idx > 0)
			idx = p[idx-1];
		
		if(t[idx] == t[i])
			idx++;
		
		p[i] = idx;
	}
}

int sobe(int pref, char c){
	if(memo2[pref][c-'a']) return dp2[pref][c-'a'];
	if(pref == 0) return c == t[pref];
	
	memo2[pref][c-'a'] = 1;
	
	int ans;
	
	if(c == t[pref]) ans = pref+1;
	else ans = sobe(p[pref-1], c);
	
	
	return dp2[pref][c-'a'] = ans;
}

int solve(int pos, int pref){
	if(pref == (int)t.size()) return INF;
	if(pos == (int)s.size()) return 0;
	if(memo[pos][pref]) return dp[pos][pref];
	memo[pos][pref] = 1;
	
	int ans;
	
	int newPref = sobe(pref, s[pos]);
	
	ans = min(1 + solve(pos+1, pref), solve(pos+1, newPref));
	
	return dp[pos][pref] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(getline(cin, s)){
		getline(cin, t);
		if(s=="" || t==""){
			cout << "0\n";
			continue;
		}
		build();
		memset(memo, 0, sizeof memo);
		memset(memo2, 0, sizeof memo2);
		cout << solve(0, 0) << "\n";
	}
	
	
	return 0;
}
