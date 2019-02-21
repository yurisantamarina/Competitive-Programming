#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010

int l[MAXN], r[MAXN], n, m, cor[MAXN];
vector<int> g[MAXN];

bool inter(int i, int j){
	if(l[i] >= r[j]) return false;
	if(r[i] <= l[j]) return false;
	if(l[i] >= l[j] && r[i] <= r[j]) return false;
	if(l[j] >= l[i] && r[j] <= r[i]) return false;
	return true;
}

bool dfs(int u){
	bool ans = true;
	for(int &v : g[u]){
		if(!ans) return false;
		if(cor[v] == -1){
			cor[v] = cor[u] ^ 1;
			ans = ans && dfs(v);
		}else{
			if(cor[v] == cor[u]) return false;
		}
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &l[i], &r[i]);
		if(l[i] > r[i]) swap(l[i], r[i]);
	}
	
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if(inter(i, j)){
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}
	
	memset(cor, -1, sizeof cor);
	bool ans = true;
	for (int i = 0; ans && i < m; i++)
	{
		if(cor[i] == -1){
			cor[i] = 0;
			ans = ans && dfs(i);
		}
	}
	
	if(ans){
		for (int i = 0; i < m; i++)
		{
			if(cor[i]) printf("i");
			else printf("o");
		}
		printf("\n");
	}else{
		printf("Impossible\n");
	}
	
	return 0;
}
