#include <bits/stdc++.h>

using namespace std;

int tempo = 1, cnt = 0;
int dx[]={1, 0, -1, 0};
int dy[]={0, 1, 0, -1};
int n, m, tc;
int seen[1010][1010];
char grid[1010][1010];

bool pode(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && seen[x][y] < tempo && grid[x][y] == '#';
}

void dfs(int x, int y){
	seen[x][y] = tempo;
	cnt++;
	
	for (int i = 0; i < 4; i++)
	{
		if(pode(x + dx[i], y + dy[i]))
			dfs(x + dx[i], y + dy[i]);
	}
	
}

int main(){
	cin >> tc;
	while (tc--)
	{
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> grid[i][j];
		
		long long ans = 0;
		tempo++;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(pode(i, j)){
					cnt = 0;
					dfs(i, j);
					ans += ((long long)cnt * cnt);
				}
			}
			
		}
		
		if(ans % (n * m) == 0) cout << ans / (n * m) << "\n";
		else{
			int g = __gcd(ans, (long long)n * m);
			cout << ans / g << " / " << (n * m) / g << "\n";
		}
	}
	
	return 0;
}
