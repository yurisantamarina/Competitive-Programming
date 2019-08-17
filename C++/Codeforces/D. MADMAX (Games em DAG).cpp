#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define MAXN 102
int n, m;
vector<pair<int, char> > g[MAXN];
bool dp[MAXN][MAXN][2][28];
char memo[MAXN][MAXN][2][28];

bool solve(int u1, int u2, int turn, int lst){
	if(memo[u1][u2][turn][lst]) return dp[u1][u2][turn][lst];
	memo[u1][u2][turn][lst] = 1;
	
	bool ans;
	int v;
	char c;
	if(turn == 0){//se uma jogada ja der true, é possivel que o primeiro jogador ganhe
		ans = false;
		for (int i = 0; !ans && i < g[u1].size(); i++)
		{
			v = g[u1][i].F;
			c = g[u1][i].S;
			
			if(c-'a'+1 >= lst) ans |= solve(v, u2, turn^1, c-'a'+1);
		}
	}else{//se uma jogada der false, nao tem como o segundo jogador ganhar
		ans = true;
		for (int i = 0; ans && i < g[u2].size(); i++)
		{
			v = g[u2][i].F;
			c = g[u2][i].S;
			
			if(c-'a'+1 >= lst) ans &= solve(u1, v, turn^1, c-'a'+1);
		}
	}
	
	return dp[u1][u2][turn][lst] = ans;
}

int main(){
	cin >> n >> m;
	int u, v;
	char c;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> c;
		g[u].pb(mp(v, c));
	}
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if(solve(i, j, 0, 0)) cout << "A";
			else cout << "B";
		}
		cout << "\n";
	}
	
	
	
	return 0;
}
