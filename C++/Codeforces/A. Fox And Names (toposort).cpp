#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
#define pb push_back

vector<int> g[30], topo;
int n, seen[MAXN];
string s[MAXN];
bool cycle = false;


void process(int at){
	int lst = at - 1;
	int i = 0;
	
	int sz = min((int)s[lst].size(), (int)s[at].size());
	while (i < sz)
	{
		if(s[lst][i] != s[at][i]){
			g[s[lst][i] - 'a'].pb(s[at][i] - 'a');
			return;
		}
		i++;
	}
	
	if((int)s[lst].size() > (int)s[at].size())
		cycle = true;
}

void dfs(int u){
	seen[u] = 1;
	
	for(int v : g[u]){
		if(seen[v] == 0)
			dfs(v);
		else if(seen[v] == 1)
			cycle = true;
	}
	
	seen[u] = 2;
	topo.pb(u);
}

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> s[i];
		if(i > 1)
			process(i);
	}
	
	for(int i = 0; i < 26; i++)
		if(seen[i] == 0)
			dfs(i);
	
	if(cycle) printf("Impossible\n");
	else{
		reverse(topo.begin(), topo.end());
		for(int v : topo)
			printf("%c", char(v + 'a'));
		printf("\n");
	}
	
	
	return 0;
}
