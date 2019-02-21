//~ http://codeforces.com/gym/101246/problem/C

#include <bits/stdc++.h>

using namespace std;

char grid[27][27];
int mask[27];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			 cin >> grid[i][j];
			 if(grid[i][j] == '*')
				mask[j] |= (1 << i);
		}
	}
	
	int lim = (1<<n), cnt, bombs, ans = 50;
	for (int config = 0; config < lim; config++)
	{
		bombs = __builtin_popcount(config);
		cnt = 0;
		for (int i = 0; i < m; i++)
		{
			if((config | mask[i]) != config)
				cnt++;
		}
		if(cnt > bombs) continue;
		ans = min(ans, bombs);
	}
	cout << ans << "\n";
	
	
	
	return 0;
}
