#include <bits/stdc++.h>

using namespace std;
#define MAXN 510
vector<int> g[MAXN];
vector<int> ciclo;
int cor[MAXN];
bool achou = false;
stack<int> p;
pair<int, int> forb;

void acha(int v){
	while (p.size()>0 && p.top() != v){
		ciclo.push_back(p.top());
		
		p.pop();
	}
	//~ printf("sz = %d\n", p.size());
	ciclo.push_back(v);
	ciclo.push_back(ciclo[0]);
	reverse(ciclo.begin(), ciclo.end());
}

void dfs(int u, int op){
	if(achou) return;
	cor[u] = 1;
	
	if(op) p.push(u);
	int v;
	for (int i = 0; i < g[u].size(); i++)
	{
		v = g[u][i];
		if(u == forb.first && v == forb.second) continue;
		if(cor[v] == 1){
			achou = true;
			if(op == 1) acha(v);
			return;
		}
		if(cor[v] == 0) dfs(v, op);
		if(achou) return;
	}
	if(op) p.pop();
	
	cor[u] = 2;
}

int main(){
	int n, m, u, v;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		g[u].push_back(v);
	}
	
	forb = make_pair(-1, -1);
	for (int i = 1; !achou && i <= n; i++)
	{
		if(cor[i] == 0) dfs(i, 1);
	}
	
	if(!achou){
		cout << "YES\n";
		return 0;
	}
	for (int i = 0; i < (int)ciclo.size()-1; i++)
	{
		forb = make_pair(ciclo[i], ciclo[i+1]);
		achou = false;
		memset(cor, 0, sizeof cor);
		for(int j = 1; j <= n; j++){
			if(cor[j] == 0) dfs(j, 0);
		}
		if(!achou){
			cout << "YES\n";
			return 0;
		}
	}
	cout << "NO\n";
	
	
	return 0;
}
