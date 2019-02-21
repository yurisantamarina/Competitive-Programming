#include <bits/stdc++.h>

using namespace std;

#define MAXN 500010
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 20000000000000000LL
typedef long long int ll;
#define gc getchar // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

struct node{
	vector<int> alt;
	vector<int> acc;
	node(){}
	node(int len){
		alt.resize(len);
		acc.resize(len, 0);
	}
};

int h[MAXN];
int letra[MAXN];
int ini[MAXN];
int fim[MAXN];
int maskGlobal;
vector<int> euler;
vector<int> g[MAXN];
node st[4*MAXN];

inline void merge(int no, int esq, int dir){
	int i = 0, j = 0, sz1 = (int)st[esq].alt.size(), sz2 = (int)st[dir].alt.size();
	st[no] = node(sz1 + sz2);
	int sz = 0;
	
	while (i < sz1 && j < sz2)
	{
		if(h[st[esq].alt[i]] < h[st[dir].alt[j]]){
			st[no].alt[sz] = st[esq].alt[i];
			st[no].acc[sz] ^= (1<<letra[st[esq].alt[i]]);
			sz++; i++;
		}else{
			st[no].alt[sz] = st[dir].alt[j];
			st[no].acc[sz] ^= (1<<letra[st[dir].alt[j]]);
			sz++; j++;
		}
	}
	while (i < sz1)
	{
		st[no].alt[sz] = st[esq].alt[i];
		st[no].acc[sz] ^= (1<<letra[st[esq].alt[i]]);
		sz++; i++;
	}
	while (j < sz2)
	{
		st[no].alt[sz] = st[dir].alt[j];
		st[no].acc[sz] ^= (1<<letra[st[dir].alt[j]]);
		sz++; j++;
	}
	for (int i = 1; i < sz; i++)
	{
		st[no].acc[i] ^= st[no].acc[i-1];
	}
}

inline void build(int no, int l, int r){
	if(l==r){
		st[no] = node(1);
		st[no].alt[0] = euler[l];
		st[no].acc[0] = 1<<letra[euler[l]];
		return;
	}
	int mid = (l+r)/2;
	int nxt = 2*no;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	merge(no, nxt, nxt+1);
}

int lvl;

inline int getL(int no){
	int lo = 0, hi = (int)st[no].alt.size()-1, mid;
	int ans = hi+10;
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(h[st[no].alt[mid]] == lvl){
			ans = min(ans, mid);
			hi = mid-1;
		}else if(h[st[no].alt[mid]] > lvl){
			hi = mid-1;
		}else lo = mid+1;
	}
	
	return ans;
}

inline int getR(int no){
	int lo = 0, hi = (int)st[no].alt.size()-1, mid;
	int ans = -1;
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(h[st[no].alt[mid]] == lvl){
			ans = max(ans, mid);
			lo = mid+1;
		}else if(h[st[no].alt[mid]] > lvl){
			hi = mid-1;
		}else lo = mid+1;
	}
	
	return ans;
}

inline void calc(int no){
	int l = getL(no);
	int r = getR(no);
	if(l > r) return;
	
	maskGlobal ^= (st[no].acc[r] ^ (l==0 ? 0 : st[no].acc[l-1]));
}

inline void query(int no, int l, int r, int i, int j){
	if(r < i || l > j) return;
	if(i <= l && r <= j){
		calc(no);
		return;
	}
	int mid = (l+r)/2;
	int nxt = 2*no;
	query(nxt, l, mid, i, j);
	query(nxt+1, mid+1, r, i, j);
}

inline void dfs(int u, int pai){
	h[u] = h[pai] + 1;
	ini[u] = (int)euler.size();
	euler.pb(u);
	for(int v : g[u]){
		if(v!=pai) dfs(v, u);
	}
	fim[u] = (int)euler.size() - 1;
}

int main(){
	int n, q, u, cnt=0;
	char c;
	scanint(n);
	scanint(q);
	for (int i = 1; i < n; i++)
	{
		scanint(u);
		u--;
		g[u].pb(i);
		g[i].pb(u);
	}
	for (int i = 0; i < n; i++)
	{
		c = gc();
		letra[i] = c-'a';
	}
	h[0] = 0;
	dfs(0, 0);
	build(1, 0, n-1);
	
	for (int i = 0; i < q; i++)
	{
		maskGlobal = 0;
		scanint(u);
		scanint(lvl);
		u--;
		query(1, 0, n-1, ini[u], fim[u]);
		
		if(__builtin_popcount(maskGlobal) > 1) printf("No\n");
		else printf("Yes\n");
	}
	
	
	return 0;
}



//BEST
#include <bits/stdc++.h>

using namespace std;

#define MAXN 500010
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 1000000000
typedef long long int ll;

vector<int> g[MAXN];
vector<pair<int, int> > nivel[MAXN];
int ini[MAXN];
int fim[MAXN];
int letra[MAXN];
int tempo = 1;

void dfs(int u, int pai, int p){
	ini[u] = tempo++;
	nivel[p].pb(mp(ini[u], 1 << letra[u]));
	
	for(int v : g[u]){
		if(v != pai) dfs(v, u, p+1);
	}
	
	fim[u] = tempo++;
}

void build(){
	
	for (int i = 1; i < MAXN; i++)
	{
		if((int)nivel[i].size() == 0) break;
		for (int j = 1; j < (int)nivel[i].size(); j++)
		{
			nivel[i][j].S ^= nivel[i][j-1].S;
		}
	}
	
}

string solve(int u, int h){
	int l, r;
	
	l = lower_bound(nivel[h].begin(), nivel[h].end(), mp(ini[u], -1)) - nivel[h].begin();
	r = upper_bound(nivel[h].begin(), nivel[h].end(), mp(fim[u], INF)) - nivel[h].begin();
	r--;
	if(l > r) return "Yes";
	
	int mask = nivel[h][r].S ^ (l == 0 ? 0 : nivel[h][l-1].S);
	
	return __builtin_popcount(mask) > 1 ? "No" : "Yes";
}

int main(){
	
	int n, q, u, h;
	string s;
	scanf("%d %d", &n, &q);
	for (int i = 1; i < n; i++)
	{
		scanf("%d", &u);
		u--;
		g[u].pb(i);
		g[i].pb(u);
	}
	cin >> s;
	for (int i = 0; i < n; i++)
	{
		letra[i] = s[i] - 'a';
	}
	dfs(0, 0, 1);
	build();
	
	for (int i = 0; i < q; i++)
	{

		scanf("%d %d", &u, &h);
		u--;
		printf("%s\n", solve(u, h).c_str());
	}
	
	
	
	
	
	
	
	return 0;
}
