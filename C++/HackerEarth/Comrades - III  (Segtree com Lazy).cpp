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

#define MAXN 100010

struct node{
	int awake, sleep;
	node(){}
	node(int a, int b){
		awake = a;
		sleep = b;
	}
	node operator + (node b){
		return node(awake + b.awake, sleep + b.sleep);
	}
};

node st[4*MAXN];
int lazy[4*MAXN];
vector<int> g[MAXN];
vector<int> gPlano;
int pos[MAXN];
int tamSub[MAXN];
int n, q;

void dfs(int u){
	pos[u] = gPlano.size();
	//~ cout << u+1 << " esta na posicao " << gPlano.size() << endl;
	gPlano.pb(u);
	tamSub[u] = 1;
	
	for (int i = 0; i < g[u].size(); i++)
	{
		dfs(g[u][i]);
		tamSub[u] += tamSub[g[u][i]];
	}	
	
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(1, 0);
		lazy[no] = -1;
		return;
	}
	int nxt=2*no, mid = (l+r)/2;
	
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no] = st[nxt] + st[nxt+1];
	lazy[no] = -1;
}

void update(int no, int l, int r, int i, int j, int op){
	int nxt = 2*no;
	
	if(lazy[no] != -1){
		if(lazy[no]==0){
			st[no].sleep += st[no].awake;
			st[no].awake = 0;
		}else{
			st[no].awake += st[no].sleep;
			st[no].sleep = 0;
		}
		
		if(l!=r){
			lazy[nxt] = lazy[no];
			lazy[nxt+1] = lazy[no];
		}
		
		lazy[no] = -1;
	}
	
	if(j<l || i>r) return;
	
	if(i<=l && r<=j){
		if(op==1){
			st[no].awake += st[no].sleep;
			st[no].sleep = 0;
		}else{
			st[no].sleep += st[no].awake;
			st[no].awake = 0;
		}
		
		if(l!=r){
			lazy[nxt] = op;
			lazy[nxt+1] = op;
		}
		
		return;
	}
	
	int mid = (l+r)/2;
	
	update(nxt, l, mid, i, j, op);
	update(nxt+1, mid+1, r, i, j, op);
	
	st[no] = st[nxt] + st[nxt+1];
}

node query(int no, int l, int r, int i, int j){
	int nxt = 2*no;
	
	if(lazy[no]!=-1){
		if(lazy[no]==0){
			st[no].sleep += st[no].awake;
			st[no].awake = 0;
		}else{
			st[no].awake += st[no].sleep;
			st[no].sleep = 0;
		}
		
		if(l!=r){
			lazy[nxt] = lazy[no];
			lazy[nxt+1] = lazy[no];
		}
		
		lazy[no] = -1;
	}
	
	if(j<l || i>r) return node(0, 0);
	if(i<=l && r<=j) return st[no];
	
	int mid = (l+r)/2;
	
	return query(nxt, l, mid, i, j) + query(nxt+1, mid+1, r, i, j);
}

int main () {
	cin >> n;
	int root, u;
	for (int i = 0; i < n; i++)
	{
		cin >> u;
		if(u){
			u--;
			g[u].pb(i);
		}else root = i;
	}
	
	dfs(root);
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << gPlano[i]+1 << " " << pos[gPlano[i]] << endl;
	//~ }
	//~ cout << endl;
	
	build(1, 0, n-1);
	
	cin >> q;
	int op, no;
	for (int i = 0; i < q; i++)
	{
		cin >> op >> no;
		no--;
		if(op==1){
			//~ cout << pos[no]+1 << " " << pos[no]+tamSub[no]-1 << endl;
			update(1, 0, n-1, pos[no]+1, pos[no]+tamSub[no]-1, 1);
		}else if(op==2){
			//~ cout << pos[no]+1 << " " << pos[no]+tamSub[no]-1 << endl;
			update(1, 0, n-1, pos[no]+1, pos[no]+tamSub[no]-1, 0);
		}else{
			//~ cout << pos[no]+1 << " " << pos[no]+tamSub[no]-1 << endl;
			cout << query(1, 0, n-1, pos[no]+1, pos[no]+tamSub[no]-1).awake << "\n";//<< " " << query(1, 0, n-1, pos[no]+1, pos[no]+tamSub[no]-1).sleep << "\n";
		}
	}
	
	
	
	return 0;
}
