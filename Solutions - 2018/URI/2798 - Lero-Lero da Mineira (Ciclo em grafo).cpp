#include <bits/stdc++.h>

using namespace std;
#define MAXN 300
typedef long long int ll;

set<char> g[MAXN];
string regra[MAXN];
int vis[MAXN];
bool cycle = false;

string solve(string &s){
	string ans = "";
	for(char c : s){
		if(regra[c].size() == 0) ans += c;
		else ans += solve(regra[c]);
	}
	return ans;
}

void dfs(char u){
	if(cycle) return;
	vis[u] = 1;
	for(char c : g[u]){
		if(vis[c] == 1){
			cycle = true;
			return;
		}else if(vis[c] == 0)
			dfs(c);
	}
	vis[u] = 2;
}

int main(){
	int n;
	char c;
	string op;
	
	for (int i = 0; i < 26; i++)
		regra[i] = "";
	
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> c >> op;
		if(op.size() == 1 && c == op[0]) continue;
		for(char ch : op)
			g[c].insert(ch);
		
		regra[c] = op;
	}
	string s;
	int k;
	cin >> k;
	cin >> s;
	
	for(char c : s){
		if(vis[c] == 0)
			dfs(c);
	}
	
	if(cycle){
		cout << "-1\n";
		return 0;
	}
	
	cout << solve(s) << "\n";
	
	
	return 0;
}
