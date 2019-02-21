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

struct node{
	int sum, l, r;
};

unordered_map<int, int> mapa, rev;
int nxt;
node st[10101010];
int val[MAXN];
int ini[MAXN];
int fim[MAXN];
int root[MAXN];
vector<int> g[MAXN];
vector<int> euler;
set<int> s;

void dfs(int u, int pai){
	euler.pb(u);
	ini[u] = (int)euler.size()-1;
	
	for(int v : g[u]){
		if(v != pai) dfs(v, u);
	}
	
	fim[u] = (int)euler.size()-1;
}

int update(int no, int l, int r, int pos, int x){
	if(pos < l || pos > r) return no;
	int clone = nxt++;
	st[clone] = st[no];
	if(l==r){
		st[clone].sum += x;
		return clone;
	}
	
	int mid = (l+r)/2;
	st[clone].l = update(st[clone].l, l, mid, pos, x);
	st[clone].r = update(st[clone].r, mid + 1, r, pos, x);
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	return clone;
}

int query(int noL, int noR, int l, int r, int k){
	if(l == r) return l;
	int sumEsq = st[st[noR].l].sum - st[st[noL].l].sum;
	int mid = (l+r)/2;
	if(sumEsq < k) return query(st[noL].r, st[noR].r, mid+1, r, k - sumEsq);
	return query(st[noL].l, st[noR].l, l, mid, k);
}

int n, q;

void reset(){
	nxt = 1;
	for (int i = 0; i <= n; i++)
	{
		g[i].clear();
	}
	euler.clear();
	mapa.clear();
	rev.clear();
	s.clear();
}

int main(){
	int tc, u, v, l, r, k;
	scanint(tc);
	while (tc--)
	{
		reset();
		scanint(n);
		scanint(q);
		for (int i = 1; i <= n; i++){
			scanint(val[i]);
			s.insert(val[i]);
		}
		for (int i = 0; i < n-1; i++)
		{
			scanint(u);
			scanint(v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		int idx = 0;
		for(auto i : s){
			mapa[i] = idx;
			rev[idx] = i;
			idx++;
		}
		
		euler.pb(0);
		dfs(1, 1);
		root[0] = 0;
		for (int i = 1; i < (int)euler.size(); i++)
			root[i] = update(root[i-1], 0, n-1, mapa[val[euler[i]]], 1);
		
		
		for (int i = 0; i < q; i++)
		{
			scanint(u);
			scanint(k);
			printf("%d ", rev[query(root[ini[u] - 1], root[fim[u]], 0, n-1, k)]);
		}
		printf("\n");
	}
	
	
	return 0;
}
