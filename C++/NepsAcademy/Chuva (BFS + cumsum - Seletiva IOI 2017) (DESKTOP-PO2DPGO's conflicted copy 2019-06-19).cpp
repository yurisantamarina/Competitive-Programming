#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101

int dx[]={1, 0, -1, 0};
int dy[]={0, 1, 0, -1};
int a[MAXN], b[MAXN], c[MAXN], d[MAXN], n, m, acc[1010][1010], ans[MAXN], grid[1010][1010], x[260], y[260], k, q;

void buildAcc(){
	for (int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			acc[i][j] += acc[i - 1][j] + acc[i][j - 1] - acc[i - 1][j - 1];
}

bool ok(int i, int j){
	return i >= 1 && i <= n && j >= 1 && j <= m && !acc[i][j];
}

void bfs(int i, int j){
	queue<pair<int, int> > q;
	q.push({i, j});
	memset(acc, 0, sizeof acc);
	acc[i][j] = 1;
	while (!q.empty())
	{
		i = q.front().first;
		j = q.front().second;
		q.pop();
		
		for(int k = 0; k < 4; k++){
			if(ok(i + dx[k], j + dy[k]) && grid[i][j] <= grid[i + dx[k]][j + dy[k]]){
				acc[i + dx[k]][j + dy[k]] = 1;
				q.push({i + dx[k], j + dy[k]});
			}
		}
	}
}

int query(int x1, int y1, int x2, int y2){
	return acc[x2][y2] - acc[x1 - 1][y2] - acc[x2][y1 - 1] + acc[x1 - 1][y1 - 1];
}

void solve(int p){
	bfs(x[p], y[p]);
	buildAcc();
	
	for (int i = 0; i < q; i++)
		ans[i] += (query(a[i], b[i], c[i], d[i]) > 0);
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &grid[i][j]);
	for (int i = 1; i <= k; i++)
		scanf("%d %d", &x[i], &y[i]);
	
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
		scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
	
	for (int i = 1; i <= k; i++)
		solve(i);
	
	for (int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
	
	
	return 0;
}
