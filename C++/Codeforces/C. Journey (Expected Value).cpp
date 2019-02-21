#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN 101010
vector<int> g[MAXN];
int n;

double dfs(int u, int pai, double p, int len){
	double ans = 0.0;
	int filhos;
	if(u == 1){
		filhos = g[u].size();
	}else{
		filhos = g[u].size() - 1;
	}
	
	if(filhos == 0) return p * len;
	
	for(int v : g[u]){
		if(v == pai) continue;
		ans += dfs(v, u, p / filhos, len + 1);
	}
	
	return ans;
}

int main(){
	int u, v;
	cin >> n;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	cout << fixed << setprecision(10) << dfs(1, 1, 1.0, 0) << "\n";
	
	return 0;
}
