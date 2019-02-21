#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 101100

vector<int> g[MAXN];

int dfs(int u, int pai){
	int ans = 0, v;
	vector<int> filho;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		filho.pb(dfs(v, u));
	}
	sort(filho.rbegin(), filho.rend());
	int tempo = 1;
	for (int i = 0; i < (int)filho.size(); i++)
	{
		ans = max(ans, tempo++ + filho[i]);
	}
	
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, x;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		while (cin >> x, x)
		{
			x--;
			g[i].pb(x);
			g[x].pb(i);
		}
		
	}
	cin >> x;
	x--;
	cout << dfs(x, x) << "\n";
	
	
	
	
	return 0;
}

