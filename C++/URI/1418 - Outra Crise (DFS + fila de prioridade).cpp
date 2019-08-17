#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int n, T;
vector<int> g[MAXN];

int get(int sz){
	int ans = (T * sz) / 100;
	
	if((T * sz) % 100 != 0) ans++;
	return ans;
}

int dfs(int u){
	int ans = 0;
	if((int)g[u].size() == 0) ans = 1; //folha
	
	int qtd = get((int)g[u].size());
	priority_queue<int, vector<int>, greater<int> > pq;
	
	for(int v : g[u]){
		pq.push(dfs(v));
	}
	while (qtd-- > 0)
	{
		ans += pq.top();
		pq.pop();
	}
	return ans;
}

void reset(){
	for (int i = 0; i <= n; i++)
		g[i].clear();
}

int main(){
	int x, ans;
	while (scanint(n), n != 0)
	{
		scanint(T);
		if(!n && !T) break;
		reset();
		for (int i = 1; i <= n; i++)
		{
			scanint(x);
			g[x].pb(i);
		}
		ans = dfs(0);
		
		printf("%d\n", ans);
	}
	
	
	return 0;
}
