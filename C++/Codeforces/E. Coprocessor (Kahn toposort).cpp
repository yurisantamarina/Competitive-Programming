#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
vector<int> g[MAXN];
queue<int> q[2];
int type[MAXN], in[MAXN], n, m;

int solve(){
	for (int i = 0; i < n; i++)
		if(in[i] == 0) q[type[i]].push(i);
	
	int turn = 0, ans = 0, u, v;
	
	while (1)
	{
		if(q[0].empty() && q[1].empty()) break;
		if(q[turn].empty()){
			turn ^= 1;
			continue;
		}
		ans += (turn == 1);
		
		while (!q[turn].empty())
		{
			u = q[turn].front(); q[turn].pop();
			for (int i = 0; i < (int)g[u].size(); i++)
			{
				v = g[u][i];
				in[v]--;
				if(in[v] == 0) q[type[v]].push(v);
			}
		}
		turn ^= 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> type[i];
	
	int u, v;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		g[v].push_back(u);
		in[u]++;
	}
	
	cout << solve() << "\n";
	
	return 0;
}
