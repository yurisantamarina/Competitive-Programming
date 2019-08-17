#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
int nxt[MAXN][20], sz[MAXN], tc, n, q, p[MAXN];
string s;

void kmp(){
	int idx = 0;
	p[0] = 0;
	for (int i = 1; i < s.size(); i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx - 1];
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
		if(p[i] > 0) nxt[i + 1][0] = p[i];
	}
}

int dfs(int u){
	if(sz[u]) return sz[u];
	sz[u] = 1;
	if(nxt[u][0] != u)
		sz[u] += dfs(nxt[u][0]);
	return sz[u];
}

void build(){
	for(int j = 1; j < 19; j++)
		for (int i = 1; i <= n; i++)
			nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
	
	for (int i = 1; i <= n; i++){
		dfs(i);
		//~ cout << "sz: " << i << " = " << sz[i] << endl;
	}
}

int climb(int x, int k){
	//~ printf("subindo %d com %d\n", k, x);
	for (int i = 0; i < 19; i++)
		if(k & (1 << i))
			x = nxt[x][i];
	return x;
}

int solve(int x, int k){
	if(sz[x] < k) return -1;
	return climb(x, sz[x] - k);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> tc;
	while (tc--)
	{
		cin >> n >> q;
		cin >> s;
		for (int i = 0; i <= n; i++){
			nxt[i][0] = i;
			sz[i] = 0;
		}
		
		kmp();
		
		build();
		
		int x, k;
		while (q--)
		{
			cin >> x >> k;
			cout << solve(x, k) << "\n";
		}
	}
	
	return 0;
}
