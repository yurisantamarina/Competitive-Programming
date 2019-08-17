//~ https://codeforces.com/gym/101873

#include <bits/stdc++.h>

using namespace std;
#define MAXN 18
#define F first
#define S second
#define INF 1000000
#define mp make_pair

int n, m, k, idx = 0;
string s[MAXN + 3];
int cost[MAXN + 3][MAXN + 3];
pair<int, int> dp[MAXN + 2][(1 << MAXN) + 3];
char grid[MAXN + 3][MAXN + 3];
bool ins[MAXN + 3];

bool inside(int a, int b){
	return s[b].find(s[a]) != string::npos;
}

int getCost(int i, int j){
	int lim = min((int)s[i].size(), (int)s[j].size());
	for (int len = lim; len >= 1; len--)
		if(s[i].substr((int)s[i].size() - len) == s[j].substr(0, len))
			return (int)s[j].size() - len;
	
	return (int)s[j].size();
}

void preprocess(){	
	vector<string> aux;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			if(i != j && inside(i, j))
				ins[i] = true;
	
	for (int i = 0; i < k; i++)
		if(!ins[i])
			aux.push_back(s[i]);
	
	k = (int)aux.size();
	for (int i = 0; i < k; i++)
		s[i] = aux[i];
	
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			if(i != j)
				cost[i][j] = getCost(i, j);
}

void recover(int u){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			grid[i][j] = '$';
	
	int mask = (1 << k) - 1, nwmask, lin, col, nwlin, nwcol;
	pair<int, int> at;
	while (mask > 0)
	{
		at = dp[u][mask];
		lin = at.F; col = at.S;
		for (int i = col - s[u].size() + 1, j = 0; i <= col; i++, j++)
			grid[lin][i] = s[u][j];
		
		
		nwmask = mask ^ (1 << u);
		
		for (int v = 0; v < k; v++)
		{
			if(!(nwmask & (1 << v))) continue;
			
			at = dp[v][nwmask];
			lin = at.F; col = at.S;
			nwlin = lin; nwcol = col;
			
			if(m - (col + 1) >= cost[v][u]){
				nwlin = lin;
				nwcol = col + cost[v][u];
			}else{
				nwlin = lin + 1;
				nwcol = (int)s[u].size() - 1;
			}
			
			if(mp(nwlin, nwcol) == dp[u][mask]){
				
				mask = nwmask;
				u = v;
				break;
			}
		}
		
		
		if(__builtin_popcount(mask) == 1){
			for (int i = 0; i < s[u].size(); i++)
				grid[0][i] = s[u][i];
			break;
		}
		
	}
}

int main(){
	
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++)
	{
		cin >> s[i];
		if(s[i].size() > m){
			cout << "impossible\n";
			return 0;
		}
	}
	
	
	preprocess();

	for (int i = 0; i < k; i++)
		for(int j = 0; j < k; j++)
			dp[j][1 << i] = (i == j) ? mp(0, (int)s[i].size() - 1) : mp(INF, INF);
	
	
	int lin, nwlin, col, nwcol, nwmask;
	pair<int, int> at;
	
	int lst = (k == 1) ? 0 : -1;
	for(int mask = 0; mask < (1 << k); mask++){
		if(__builtin_popcount(mask) <= 1) continue;
		for(int u = 0; u < k; u++){
			if(!(mask & (1 << u))) continue;
			dp[u][mask] = {INF, INF};
			
			nwmask = mask ^ (1 << u);
			for (int v = 0; v < k; v++)
			{
				if(!(nwmask & (1 << v))) continue;
				at = dp[v][nwmask];
				lin = at.F; col = at.S;
				nwlin = lin; nwcol = col;
				if(m - (col + 1) >= cost[v][u]){
					nwlin = lin;
					nwcol = col + cost[v][u];
				}else{
					nwlin = lin + 1;
					nwcol = (int)s[u].size() - 1;
				}
				dp[u][mask] = min(dp[u][mask], mp(nwlin, nwcol));
			}
			
			if(mask == (1 << k) - 1)
				if(dp[u][mask].F < n && dp[u][mask].S < m) 
					lst = u;
		}
	}
	
	if(lst == -1){
		cout << "impossible\n";
		
	}else{
		recover(lst);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(grid[i][j] == '$') grid[i][j] = 'A';
				cout << grid[i][j];
			}
			cout << "\n";
		}
		
	}
	return 0;
}
