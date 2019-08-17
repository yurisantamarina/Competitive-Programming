#include <bits/stdc++.h>

using namespace std;
#define MAXN 50110
#define pb push_back

vector<int> g[MAXN], vet;
char vis[MAXN], clique[MAXN], desconexo[MAXN];
int n, m, u, v, deg[MAXN];

bool compare(int a, int b){
	return deg[a] < deg[b];
}

int main(){
	while (scanf("%d %d", &n, &m) != EOF)
	{
		if(!n && !m) break;
		vet.clear();
		for (int i = 1; i <= n; i++)
			g[i].clear(), vis[i] = 0, vet.pb(i), deg[i] = 0;
		
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
			deg[u]++;
			deg[v]++;
		}
		sort(vet.begin(), vet.end(), compare);
		//~ for (int i = 0; i < vet.size(); i++)
		//~ {
			//~ cout << vet[i] << " ";
		//~ }
		//~ cout << endl;
		int cnt;
		clique[n-1] = 1;
		vis[vet[n-1]] = 1;
		for (int i = n-2; i >= 0; i--)
		{
			cnt = 0;
			clique[i] = 0;
			for(int v : g[vet[i]])
				if(vis[v]) cnt++;
			if(cnt == n-i-1) clique[i] = 1;
			vis[vet[i]] = 1;
			clique[i] = clique[i+1] && clique[i];
		}
		
		for (int i = 1; i <= n; i++)
			vis[i] = 0;
		
		bool ok = false;
		for (int i = 0; i < n; i++)
		{
			cnt = 0;
			desconexo[i] = 0;
			//~ if(i) desconexo[i] = desconexo[i-1];
			for(int v : g[vet[i]]){
				if(vis[v]){
					cnt++;
					break;
				}
			}
			if(cnt==0) desconexo[i] = 1;
			if(i) desconexo[i] = desconexo[i] && desconexo[i-1];
			
			if(i < n-1 && desconexo[i] && clique[i+1]){
				ok = true;
				break;
			}
			vis[vet[i]] = 1;
		}
		
		//~ for (int i = 0; i < n; i++)
			//~ cout << char(clique[i]+'0') << " ";
		//~ cout << endl;
		//~ for (int i = 0; i < n; i++)
			//~ cout << char(desconexo[i]+'0') << " ";
		//~ cout << endl;
		
		
		if(ok || n == 1) printf("Y\n");
		else printf("N\n");
	}
	
	
	
	return 0;
}
