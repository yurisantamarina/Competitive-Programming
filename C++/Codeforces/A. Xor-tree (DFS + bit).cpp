#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define pb push_back
#define MAXN 101010
int fim[MAXN], ini[MAXN], h[MAXN], s[MAXN], t[MAXN], bit[2][MAXN];
vector<int> euler[2], g[MAXN], ans;

int query(int pos, int op){
	int sum = 0;
	for (int i = pos; i > 0; i -= i & -i)
		sum += bit[op][i];
	return sum;
}

void updatePos(int pos, int val, int op){
	for(int i = pos; i < MAXN; i += i & -i)
		bit[op][i] += val;
}

int update(int l, int r, int op){
	updatePos(l, 1, op);
	updatePos(r+1, -1, op);
}

void dfsBuild(int u, int pai){
	h[u] = h[pai] + 1;
	ini[u] = (int)euler[0].size();
	
	euler[h[u] & 1].pb(u);
	euler[1 - (h[u] & 1)].pb(-1);
	
	for(int v : g[u]){
		if(v == pai) continue;
		dfsBuild(v, u);
	}
	
	fim[u] = (int)euler[0].size()-1;
}

void dfsSolve(int u, int pai){
	int at = query(ini[u], h[u] & 1);
	if(at & 1) at = s[u] ^ 1;
	else at = s[u];
	
	if(at != t[u]){
		update(ini[u], fim[u], (h[u] & 1));
		ans.pb(u);
	}
	
	for(int v : g[u]){
		if(v == pai) continue;
		dfsSolve(v, u);
	}
}

int main(){
	int n, u, v;
	cin >> n;
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	for (int i = 1; i <= n; i++)
		cin >> t[i];
	
	h[1] = -1;
	euler[0].pb(-1);
	euler[1].pb(-1);
	dfsBuild(1, 1);
	
	dfsSolve(1, 1);
	cout << (int)ans.size() << "\n";
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] << "\n";
	
	
	return 0;
}
