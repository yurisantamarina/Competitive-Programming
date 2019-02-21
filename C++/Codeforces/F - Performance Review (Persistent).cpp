//~ http://codeforces.com/group/eqgxxTNwgd/contest/101174/attachments

#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair
#define MAXN 101010
typedef long long int ll;

struct node{
	ll sum;
	int l, r;
};

int nxt = 1;
vector<int> g[MAXN];
int lvl[MAXN];
int tempo[MAXN];
int ini[MAXN];
int fim[MAXN];
int root[MAXN];
vector<int> euler;
int MAX_RANK;
node st[10101010];

int update(int no, int l, int r, int pos, ll val){
	if(pos < l || pos > r) return no;
	int clone = nxt++;
	st[clone] = st[no];
	if(l == r){
		st[clone].sum += val;
		return clone;
	}
	
	int mid = (l+r)/2;
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

ll query(int noL, int noR, int l, int r, int i, int j){
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return st[noR].sum - st[noL].sum;
	
	int mid = (l+r)/2;
	return query(st[noL].l, st[noR].l, l, mid, i, j) + query(st[noL].r, st[noR].r, mid+1, r, i, j);
}

void dfs(int u, int pai){
	euler.pb(u);
	ini[u] = (int)euler.size() - 1;
	
	for(int v : g[u])
		dfs(v, u);
		
	fim[u] = (int)euler.size() - 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, x, fst;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> x >> lvl[i] >> tempo[i];
		if(x == -1){
			fst = i;
		}else{
			g[x].pb(i);
		}
		MAX_RANK = max(MAX_RANK, lvl[i]);
	}
	
	euler.pb(0);
	dfs(fst, 0);
	
	root[0] = 0;
	for (int i = 1; i <= n; i++)
		root[i] = update(root[i-1], 1, MAX_RANK, lvl[euler[i]], tempo[euler[i]]);
	
	for (int i = 1; i <= n; i++)
		cout << query(root[ini[i]], root[fim[i]], 1, MAX_RANK, 1, lvl[i]-1) << "\n";
	
	
	
	return 0;
}
