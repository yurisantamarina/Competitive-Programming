#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const ll MOD = 1e9;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 50010
#define MAXQ 100010
#define gc getchar_unlocked // ou usar só getchar


int read_int(){
	char r;
	bool start=false,neg=false;
	int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}



struct query{
	int l, r, pos;
	query(){}
	query(int a, int b, int c){
		l = a;
		r = b;
		pos = c;
	}
};


int v[MAXN];
int v2[MAXN];
vector<int> g[MAXN];
vector<int> t[MAXN];
vector<int> dag[MAXN];
char vis[MAXN];
int n, q;
query queries[MAXQ];
int st[4*MAXN];
int block_size = 300;
int ans[MAXQ];
int f[MAXN];

inline void update(int no, int l, int r, int pos, int val){
	if(pos<l || pos>r) return;
	if(l==r && pos==l){
		st[no] += val;
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	
	st[no] = st[nxt] + st[nxt+1];
}

int getSum(int no, int l, int r, int i, int j){
	if(j<l || i>r) return 0;
	if(i<=l && r<=j) return st[no];
	int nxt=2*no, mid=(l+r)/2;
	
	return getSum(nxt, l, mid, i, j) + getSum(nxt+1, mid+1, r, i, j);
}

bool compare(const query &a, const query &b){
	if(a.l/block_size == b.l/block_size) return a.r < b.r;
	return a.l < b.l;
}



stack<int> p;
int comp[MAXN];
int componente;
int grau[MAXN];
int mn[MAXN];

inline void dfs1(int u){
	if(vis[u]) return;
	vis[u] = 1;
	for (int i = 0; i < g[u].size(); i++)
	{
		dfs1(g[u][i]);
	}
	p.push(u);
	//~ printf("Inserindo %d na pilha\n", u+1);
}

int MINIMO;
inline void dfs2(int u){
	if(vis[u]) return;
	vis[u] = 1;
	
	MINIMO = min(MINIMO, u);
	comp[u] = componente;
	//~ printf("%d esta na componente %d\n", u+1, componente);
	for (int i = 0; i < t[u].size(); i++)
	{
		dfs2(t[u][i]);
	}
}

int dfs3(int u){
	if(vis[u]){
		return v2[u]==-1 ? u : v2[u];
	}
	vis[u] = 1;
	
	int m = v2[u];
	for (auto i : dag[u])
	{
		m = min(m, dfs3(i));
	}
	
	return v2[u] = m;
}
inline void cria(){
	//~ memset(vis, 0, sizeof vis);
	while (!p.empty()) p.pop();
	for(int i=0; i<n; i++) if(!vis[i]) dfs1(i);
	
	componente=0;
	memset(vis, 0, sizeof vis);
	while (!p.empty())
	{
		int u = p.top();
		p.pop();
		if(vis[u]) continue;
		MINIMO = 1e9;
		dfs2(u);
		v2[componente] = MINIMO;
		//~ printf("minimo da componente %d = %d\n", componente, MINIMO+1);
		componente++;
		
	}
	
	for (int u = 0; u < n; u++)
	{
		for (int i = 0; i < g[u].size(); i++)
		{
			if(comp[u] != comp[g[u][i]]){
				//~ printf("%d esta na componente %d e %d esta na componente %d\n", u+1, comp[u], g[u][i]+1, comp[g[u][i]]);
				dag[comp[u]].pb(comp[g[u][i]]);
				grau[comp[g[u][i]]]++;
			}
		}
	}
	
	queue<int> q;
	for (int i = 0; i < componente; i++)
	{
		if(grau[i]==0) q.push(i);
		//~ printf("Grau da componente %d = %d\n", i, grau[i]);
	}
	
	int c;
	memset(vis, 0, sizeof vis);
	while (!q.empty())
	{
		c = q.front(); q.pop();
		
		if(vis[c]) continue;
		dfs3(c);
		//~ printf("Comecando dfs na componente %d\n", c);
		for (auto i : dag[c])
		{
			
			grau[i]--;
			if(grau[i]==0) q.push(i);
		}
	}
	
	//~ for (int i = 0; i < componente; i++)
	//~ {
		//~ printf("%d ", v2[i]);
	//~ }
	//~ cout << endl;
	
	for (int i = 0; i < n; i++)
	{
		v[i] = v2[comp[i]];
	}
	
	
	
	
}

inline void add(int pos){
	int val = v[pos];
	//~ f[val]++;
	//~ if(f[val]==1){
		update(1, 0, n-1, val, 1);
	//~ }
}

inline void del(int pos){
	int val = v[pos];
	//~ f[val]--;
	//~ if(f[val]==0){
		update(1, 0, n-1, val, -1);
	//~ }
}


int kesimo(int no, int l, int r, int k){
	if(l==r) return l;
	
	int nxt = 2*no;
	int x = st[nxt];
	
	int mid = (l+r)/2;
	if(x>=k) return kesimo(nxt, l, mid, k);
	else return kesimo(nxt+1, mid+1, r, k-x);
}

int getAns(int l, int r){
	//~ printf("range %d, %d\n", l, r);
	int k = (r-l+1)/2;
	int kth = kesimo(1, 0, n-1, k);
	//~ printf("kth = %d\n", kth);
	int prof = getSum(1, 0, n-1, 0, kth);
	int alu = (r-l+1) - prof;
	int dif = abs(prof-alu);
	//~ printf("prof = %d  alu = %d\n", prof, alu);
	
	int a, b;
	a = getSum(1, 0, n-1, 0, kth-1);
	b = (r-l+1) - a;
	
	//~ printf("newprof = %d  newalu = %d\n", a, b);
	if(abs(a-b) <= dif){
		if(a==0) return 0;
		//~ oioi;
		//~ printf("kesimo [0, %d]  k = %d\n", kth-1, kesimo(1, 0, n-1, a));
		return kesimo(1, 0, n-1, a);
	}else{
		return kth;
	}
}


int main () {
	
	int u;
	//~ cin >> n >> q;
	n = read_int();
	q = read_int();
	for (int i = 0; i < n; i++)
	{
		//~ cin >> u;
		u = read_int();
		u--;
		g[i].pb(u);
		t[u].pb(i);
	}
	
	memset(v2, -1, sizeof v2);
	cria();
	
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << v[i]+1 << " ";
	//~ }
	//~ cout << endl;
	
	
	int l, r, currL=0, currR=0;
	for (int i = 0; i < q; i++)
	{
		//~ cin >> l >> r;
		l = read_int();
		r = read_int();
		l--;
		r--;
		queries[i] = query(l, r, i);
	}
	
	sort(queries, queries+q, compare);
	
	//~ memset(st, 0, sizeof st);
	//~ memset(f, 0, sizeof f);
	
	for (int i = 0; i < q; i++)
	{
		l = queries[i].l;
		r = queries[i].r;
		
		while (currL < l)
		{
			del(currL);
			currL++;
		}
		while (currR <= r)
		{
			add(currR);
			currR++;
		}
		while (currL > l)
		{
			add(currL-1);
			currL--;
		}
		while (currR > r+1)
		{
			del(currR-1);
			currR--;
		}
		
		
		//~ cout << "range: " << l+1 << ", " << r+1 << endl;
		
		//~ for(int k=0; k<n; k++) cout << f[k] << " ";
		//~ cout << endl;
		ans[queries[i].pos] = getAns(l, r);
		//~ cout << getSum(1, 0, n-1, 0, 7) << endl << endl;
	}
	
	
	for (int i = 0; i < q; i++)
	{
		printf("%d\n", ans[i]+1);
	}
	
	
	
	return 0;
}
