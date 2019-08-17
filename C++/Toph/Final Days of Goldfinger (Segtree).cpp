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
const ll MOD = 0;
const int INF = 1e9 + 10;
const ll LINF = 1e18 + 10;
#define MAXN 100010

struct node{
	int left, right;
	int mn, mx;
	int l, r;
	node(){}
	node(int a, int b, int c, int d, int e, int f){
		left = a;
		right = b;
		mn = c;
		mx = d;
		l = e;
		r = f;
	}
};

int v[MAXN];
node st[4*MAXN];

node merge(node &esq, node &dir){
	//~ printf("%d, %d\n%d, %d\n%d, %d\n", esq.left, esq.right, esq.mn, esq.mx, esq.l, esq.r);
	//~ printf("%d, %d\n%d, %d\n%d, %d\n", dir.left, dir.right, dir.mn, dir.mx, dir.l, dir.r);
	int vv[4]={esq.left, esq.right, dir.left, dir.right};
	int p[4];
	int maximo=-INF, auxLeft, auxRight, auxMn, auxMx, auxL, auxR;
	for (int i = 0; i < 4; i++)
	{
		for (int j = i+1; j < 4; j++)
		{
			if(vv[j] - vv[i] >= maximo){//tratar se for igual
				maximo = vv[j] - vv[i];
				auxLeft = vv[i];
				auxRight = vv[j];
			}
		}
	}
	
	vv[0] = esq.mn; vv[1] = esq.mx; vv[2] = dir.mn; vv[3] = dir.mx;
	p[0] = esq.l; p[1] = esq.r; p[2] = dir.l; p[3] = dir.r;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = i+1; j < 4; j++)
		{
			if(p[j] < p[i]) continue;
			if(vv[j] - vv[i] >= maximo){//tratar se for igual
				maximo = vv[j] - vv[i];
				auxLeft = vv[i];
				auxRight = vv[j];
			}
		}
	}
	
	auxMn = INF;
	auxL = INF;
	auxMx = -INF;
	auxR = -INF;
	for (int i = 0; i < 4; i++)
	{
		if(vv[i] <= auxMn){
			if(vv[i] == auxMn) auxL = min(auxL, p[i]);
			else auxL = p[i];
			auxMn = vv[i];
		}
		if(vv[i] >= auxMx){
			if(vv[i] == auxMx) auxR = max(auxR, p[i]);
			else auxR = p[i];
			auxMx = vv[i];
		}
	}
	
	node ans = node(auxLeft, auxRight, auxMn, auxMx, auxL, auxR);
	return ans;
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(v[l], v[l], v[l], v[l], l, l);
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	st[no] = merge(st[nxt], st[nxt+1]);
}

void update(int no, int l, int r, int pos, int val){
	if(pos<l || pos>r) return;
	if(l==r && pos==l){
		st[no] = node(val, val, val, val, pos, pos);
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = merge(st[nxt], st[nxt+1]);
}

node query(int no, int l, int r, int i, int j){
	if(j<l || i>r) return node(-INF, 0, 0, 0, 0, 0);
	if(i<=l && r<=j) return st[no];
	int nxt = 2*no;
	int mid = (l+r)/2;
	
	node esq, dir;
	esq = query(nxt, l, mid, i, j);
	dir = query(nxt+1, mid+1, r, i, j);
	if(esq.left == -INF) return dir;
	if(dir.left == -INF) return esq;
	return merge(esq, dir);
}

int main ()
{
	int t, n, q, op, pos, l, r, val, caso=1;
	cin >> t;
	while (t--)
	{
		cin >> n >> q;
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		build(1, 0, n-1);
		cout << "Case " << caso++ << ":\n";
		for (int i = 0; i < q; i++)
		{
			cin >> op;
			if(op==1){
				cin >> pos >> val;
				pos--;
				update(1, 0, n-1, pos, val);
			}else{
				cin >> l >> r;
				l--; r--;
				node ans = query(1, 0, n-1, l, r);
				cout << ans.right - ans.left << "\n";
			}
		}
		
	}
	
	
	return 0;
}
