#include <bits/stdc++.h>

using namespace std;

#define MAXN 101010
#define pb push_back

string s[MAXN];
char tmp[MAXN];
int dp[MAXN][26];
char memo[MAXN][26];
string patt;
int p[MAXN], ans = 0;
int szPatt;
int ant[MAXN];
int lst[MAXN];

void build(){
	p[0] = 0;
	int idx = 0;
	for (int i = 1; i < szPatt; i++)
	{
		idx = p[i-1];
		while(patt[idx] != patt[i] && idx > 0) idx = p[idx-1];
		if(patt[idx] == patt[i]) idx++;
		p[i] = idx;
	}
}

int get(int idx, char c){
	if(idx == 0) return c == patt[idx];
	if(memo[idx][c-'a']) return dp[idx][c-'a'];
	memo[idx][c-'a'] = 1;
	
	int ans;
	if(patt[idx] == c) ans = idx+1;
	else ans = get(p[idx-1], c);
	
	return dp[idx][c-'a'] = ans;
}

void dfs(int u, int aux){
	int idx, v;
	int sz2;
	v = lst[u];
	
	while(v > 0)
	{
		idx = aux;
		sz2 = (int)s[v].size();
		for (int i = 0; i < sz2; i++)
		{
			//~ while(s[v][i] != patt[idx] && idx > 0) idx = p[idx-1];
			//~ if(s[v][i] == patt[idx]) idx++;
			idx = get(idx, s[v][i]);
			
			if(idx == szPatt){
				ans++;
				idx = p[idx-1];
			}
		}
		dfs(v, idx);
		v = ant[v];
	}
	
	
}

int main(){
	int n, u;
	scanf("%d", &n);
	
	s[1] = "$";
	for (int i = 2; i <= n; i++)
	{
		scanf("%d %s", &u, tmp);
		s[i] = tmp;
		ant[i] = lst[u];
		lst[u] = i;
	}
	scanf("%s", tmp);
	patt = tmp;
	szPatt = (int)patt.size();
	build();
	
	dfs(1, 0);
	
	printf("%d\n", ans);
	
	
	return 0;
}
