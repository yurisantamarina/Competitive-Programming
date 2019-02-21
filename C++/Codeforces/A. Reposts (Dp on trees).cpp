//~ http://codeforces.com/contest/522/problem/A

#include <bits/stdc++.h>

using namespace std;
#define MAXN 210
#define INF 10000000000000LL
#define MOD 1000000007
#define pb push_back
typedef long long int ll;
vector<int> g[MAXN];
map<string, int> mapa;
int idx=0;

int transform(string s){
	for (int i = 0; i < (int)s.size(); i++)
	{
		s[i] = tolower(s[i]);
	}
	if(mapa.count(s)) return mapa[s];
	
	return mapa[s] = idx++;
}

int solve(int u){
	int ans = 0;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		ans = max(ans, solve(g[u][i]));
	}
	
	return ans + 1;
}

int main(){
	int n, u, v;
	string a, b, lixo;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> lixo >> b;
		u = transform(a);
		v = transform(b);
		g[v].pb(u);
	}
	
	cout << solve(transform("polycarp")) << "\n";
	
	return 0;
}
