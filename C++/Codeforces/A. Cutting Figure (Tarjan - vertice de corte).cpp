#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back

char grid[55][55];
vector<int> g[MAXN];
int d[MAXN], low[MAXN], tempo, vcorte, seen[MAXN], root, n, m, cnt = 0;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int get(int i, int j){
	return (i - 1) * m + j;
}

bool pode(int x, int y){
	return x >= 1 && y >= 1 && x <= n && y <= m && grid[x][y] == '#';
}

void dfs(int u, int pai){
	if(vcorte) return;
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	
	int nf = 0;
	bool any = false;
	for(int v : g[u]){
		if(!seen[v]){
			dfs(v, u);
			nf++;
			low[u] = min(low[u], low[v]);
			
			if(d[u] <= low[v]) any = true;
		}else if(v != pai)
			low[u] = min(low[u], d[v]);
	}
	
	if(root == u && nf >= 2) vcorte++;
	else if(root != u && any) vcorte++;
}


int main(){
	
	scanf("%d %d", &n, &m);
	int x, y;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++){
			cin >> grid[i][j];
			if(grid[i][j] == '#'){
				cnt++;
				x = i;
				y = j;
			}
		}
	
	if(cnt <= 2){
		printf("-1\n");
		return 0;
	}
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if(grid[i][j] == '#')
				for(int k = 0; k < 4; k++)
					if(pode(i + dx[k], j + dy[k]))
						g[get(i, j)].pb(get(i + dx[k], j + dy[k]));
	
	root = get(x, y);
	dfs(root, root);
	
	if(vcorte) printf("1\n");
	else printf("2\n");
	
	
	return 0;
}
