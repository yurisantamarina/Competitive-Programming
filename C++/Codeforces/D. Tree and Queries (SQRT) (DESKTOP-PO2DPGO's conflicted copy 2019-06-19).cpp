#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const ll dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const ll dy[] = {-1,0,0, 1,1, 1,-1,-1};
ll gcd (ll x, ll y) {return (y != 0 ? gcd (y, x%y) : x);}
ll lcm (ll x, ll y) {return (x / gcd (x, y) * y);}
#define MAXN 100100

struct query{
	int l, r, val, pos;
	query(){}
	query(int a, int b, int c, int d){
		l = a;
		r = b;
		val = c;
		pos = d;
	}
};

int freqMin, ans;
int block_size = 320;
query queries[MAXN];
int saida[MAXN];
vector<int> arr;
int tamSub[MAXN];
int ini[MAXN];
int cor[MAXN];
int n, q;
vector<int> g[MAXN];
int f[MAXN];
int tree[MAXN];

int read(int idx)
{
	int ret =0;
	while(idx>0)
	{
		ret+=tree[idx];
		idx-=idx&(-idx);
	}
	return ret;
}

void update(int idx, int val)
{
	while(idx<MAXN)
	{
		tree[idx]+=val;
		idx+=idx&(-idx);
	}
}

void dfs(int u, int ult){
	tamSub[u] = 1;
	arr.pb(u);
	ini[u] = arr.size()-1;
	int v;
	for (int i = 0; i < g[u].size(); i++)
	{
		v = g[u][i];
		if(v == ult) continue;
		dfs(v, u);
		tamSub[u] += tamSub[v];
	}
}

void geraVetor(){
	memset(tamSub, 0, sizeof tamSub);
	memset(ini, -1, sizeof ini);
	dfs(0, 0);
}

bool compare(query &a, query &b){
	if(a.l / block_size == b.l / block_size) return a.r < b.r;
	return a.l < b.l;
}

void add(int pos){
	int val = cor[arr[pos]];
	if(f[val] > 0) update(f[val], -1);
	f[val]++;
	if(f[val] > 0) update(f[val], 1);
}

void del(int pos){
	int val = cor[arr[pos]];
	if(f[val] > 0) update(f[val], -1);
	f[val]--;
	if(f[val] > 0) update(f[val], 1);
}

int main()
{
	int u, v;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n >> q;
	int maxCor = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> cor[i];
		maxCor = max(maxCor, cor[i]);
	}
	
	for (int i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	geraVetor();
	
	int val;
	for (int i = 0; i < q; i++)
	{
		cin >> u >> val;
		u--;
		queries[i] = query(ini[u], ini[u] + tamSub[u] - 1, val, i);
	}
	
	sort(queries, queries+q, compare);
	
	int L, R, currL=0, currR=0;
	ans = 0;
	memset(f, 0, sizeof f);
	memset(tree, 0, sizeof tree);
	
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		freqMin = queries[i].val;
		while (currL < L)
		{
			del(currL);
			currL++;
		}
		while (currR <= R)
		{
			add(currR);
			currR++;
		}
		while (currL > L)
		{
			add(currL-1);
			currL--;
		}
		while (currR > R+1)
		{
			del(currR-1);
			currR--;
		}
		
		saida[queries[i].pos] = read(MAXN) - read(freqMin-1);
	}
	
	for (int i = 0; i < q; i++)
	{
		cout << saida[i] << "\n";
	}
	
	
	
	
	return 0;
}
