#include <bits/stdc++.h>

using namespace std;
#define MAXN 10000000
int p[MAXN];
string s, t;
vector<vector<int> > dp;
vector<vector<int> > dp2;

void prefix(string &t){
	p[0] = 0;
	int idx;
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
	if(pref == 0) return dp2[pref][c-'a'] = c == t[pref] ? 1 : 0;
	if(dp2[pref][c-'a'] != -1) return dp2[pref][c-'a'];
	
	if(c == t[pref]) return dp2[pref][c-'a'] = pref+1;
	return dp2[pref][c-'a'] = sobe(p[pref-1], c);
}

int solve(int pos, int pref){
	if(pos == (int)s.size()) return 0;
	if(dp[pos][pref] != -1) return dp[pos][pref];
	
	int ans = 0, aux;
	if(s[pos] == '?'){
		
		for (char i = 'a'; i <= 'z'; i++)
		{
			aux = sobe(pref, i);
			
			if(aux == (int)t.size())
				ans = max(ans, 1 + solve(pos+1, p[aux-1]));
			else
				ans = max(ans, solve(pos+1, aux));
		}
		
	}else{
		aux = sobe(pref, s[pos]);

		if(aux == (int)t.size())
			ans = 1 + solve(pos+1, p[aux-1]);
		else
			ans = solve(pos+1, aux);
	}
	
	return dp[pos][pref] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	cin >> t;
	
	prefix(t);
	
	dp.resize((int)s.size()+1, vector<int>());
	
	for (int i = 0; i < (int)s.size(); i++)
		dp[i].resize((int)t.size()+1, -1);
	
	dp2.resize((int)t.size()+1, vector<int>());
	
	for (int i = 0; i < (int)t.size(); i++)
		dp2[i].resize(26, -1);
	
	
	cout << solve(0, 0) << "\n";
	
	
	return 0;
}
