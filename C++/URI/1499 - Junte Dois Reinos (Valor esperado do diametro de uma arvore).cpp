#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN 101010
typedef long long int ll;

vector<int> g[MAXN][2];
int dpIn[MAXN][2], dpOut[MAXN][2], dp[MAXN][2], diam, N, Q;
ll acc[MAXN];
vector<int> vet;

void dfs1(int u, int p, int op){
	dpIn[u][op] = 0;
	for(int v : g[u][op]){
		if(v == p) continue;
		dfs1(v, u, op);
		dpIn[u][op] = max(dpIn[u][op], dpIn[v][op] + 1);
	}
}

void dfs2(int u, int p, int op){
	int mx1, mx2;
	mx1 = mx2 = INT_MIN;
	dp[u][op] = max(dpIn[u][op], dpOut[u][op]);
	diam = max(diam, dp[u][op]);
	
	if(op == 1)
		vet.pb(dp[u][op] + 1);
	
	for(int v : g[u][op]){
		if(v == p) continue;
		if(dpIn[v][op] > mx1){
			mx2 = mx1;
			mx1 = dpIn[v][op];
		}else if(dpIn[v][op] > mx2){
			mx2 = dpIn[v][op];
		}
	}
	
	int at;
	for(int v : g[u][op]){
		if(v == p) continue;
		if(dpIn[v][op] == mx1) at = mx2;
		else at = mx1;
		
		dpOut[v][op] = max(2 + at, 1 + dpOut[u][op]);
		
		dfs2(v, u, op);
	}
}

void reset(){
	int mx = max(N, Q);
	for (int i = 0; i <= mx; i++)
	{
		g[i][0].clear();
		g[i][1].clear();
	}
	
}

int main(){
	int u, v;
	while (scanf("%d %d", &N, &Q) != EOF)
	{
		reset();
		for (int i = 0; i < N-1; i++)
		{
			scanf("%d %d", &u, &v);
			g[u][0].pb(v);
			g[v][0].pb(u);
		}
		for (int i = 0; i < Q-1; i++)
		{
			scanf("%d %d", &u, &v);
			g[u][1].pb(v);
			g[v][1].pb(u);
		}
		
		dpOut[1][0] = dpOut[1][1] = 0;
		diam = -1;
		vet.clear();
		dfs1(1, 1, 0);
		dfs2(1, 1, 0);
		dfs1(1, 1, 1);
		dfs2(1, 1, 1);

		sort(vet.begin(), vet.end());
		acc[(int)vet.size()] = 0;
		
		for (int i = (int)vet.size()-1; i >= 0; i--)
		{
			acc[i] = vet[i];
			if(i < (int)vet.size()-1) acc[i] += acc[i+1];
		}
		
		int id;
		ll ans = 0;
		for (int i = 1; i <= N; i++)
		{
			id = upper_bound(vet.begin(), vet.end(), diam - dp[i][0] - 1) - vet.begin();
			ans += (ll)id * diam + (ll)(Q - id) * dp[i][0] + (ll)acc[id];
		}
		printf("%.3lf\n", ((double)ans) / (ll)(N * Q));
	}
	
	
	
	
	return 0;
}
