//~ http://codeforces.com/group/kZPk3ZTzR5/contest/101165/problem/I

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;

int p[MAXN];
vector<pair<int, int> > cost[MAXN];
string s, text, patt;
ll dp[MAXN];

void kmp(int c){
	p[0] = 0;
	int idx = 0, n = (int)s.size();
	for (int i = 1; i < n; i++)
	{
		while(s[idx] != s[i] && idx > 0) idx = p[idx-1];
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
		if(idx == (int)patt.size())
			cost[i - (int)patt.size() - 1].push_back(make_pair(c, (int)patt.size()));
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int qtd, c;
	cin >> text;
	cin >> qtd;
	for (int i = 0; i < qtd; i++)
	{
		cin >> patt >> c;
		s = patt + "$" + text;
		kmp(c);
	}
	
	for (int i = 0; i < (int)text.size(); i++)
	{
		dp[i] = i ? dp[i-1] : 0;
		for (int k = 0; k < (int)cost[i].size(); k++)
			dp[i] = max(dp[i], (ll)cost[i][k].F + dp[i - cost[i][k].S]);
	}
	cout << dp[(int)text.size()-1] << "\n";
	
	
	return 0;
}
