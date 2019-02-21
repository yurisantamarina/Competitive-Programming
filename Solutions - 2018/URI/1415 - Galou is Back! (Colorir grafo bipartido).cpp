#include <bits/stdc++.h>

using namespace std;
#define MAXN 200
int dx[]={1,0,-1,0,1,-1,1,-1};
int dy[]={0,1,0,-1,-1,1,1,-1};

char grid[MAXN][MAXN], blocked[MAXN][MAXN];
int n, m, cor[MAXN][MAXN];

bool pode(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != '.'; 
}

void dfs(int x, int y, int c){
	cor[x][y] = c;
	
	
	for (int i = 0; i < 6; i++)
	{
		if(pode(x+dx[i], y+dy[i])){
			if(cor[x+dx[i]][y+dy[i]] == -1){
				dfs(x+dx[i], y+dy[i], c^1);
			}else if(cor[x+dx[i]][y+dy[i]] == c){
				blocked[x+dx[i]][y+dy[i]] = 1;
			}
		}
	}
}

void dfs2(int x, int y){
	blocked[x][y] = 1;
	for (int i = 0; i < 6; i++)
	{
		if(pode(x+dx[i], y+dy[i]) && !blocked[x+dx[i]][y+dy[i]]){
			dfs2(x+dx[i], y+dy[i]);
		}
	}
}

int main(){
	while(scanf("%d %d", &n, &m) != EOF){
		if(!n && !m) return 0;
		
		for (int i = 0; i < n; i++)
		{
			getchar();
			for (int j = 0; j < m; j++)
			{
				scanf("%c", &grid[i][j]);
				blocked[i][j] = 0;
			}
		}
		
		memset(cor, -1, sizeof cor);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(grid[i][j] == 'I'){
					if(cor[i][j] == 1) blocked[i][j] = 1;
					else dfs(i, j, 0);
				}
			}
		}
		
		
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(blocked[i][j]){
					blocked[i][j] = 0;
					dfs2(i, j);
				}
			}
		}
		memset(cor, -1, sizeof cor);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(grid[i][j] == 'I' && !blocked[i][j]) dfs(i, j, 0);
			}
		}
		
		puts("");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if(grid[i][j] == '.') printf(".");
				else if(blocked[i][j]) printf("B");
				else if(cor[i][j] == -1) printf("F");
				else printf("%c", !cor[i][j] ? '(' : ')');
			}
			printf("\n");
		}
		
	}
	
	
	return 0;
}
