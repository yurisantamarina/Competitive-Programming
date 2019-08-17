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
#define MAXN 70000
 
struct node{
	int pref, suf, total, mss;
	node(){}
	node(int a, int b, int c, int d){
		pref = a;
		suf = b;
		total = c;
		mss = d;
	}
};

int v[MAXN];
node st[4*MAXN];

node merge(node &left, node &right){
	node ans;
	ans.pref = max(left.pref, left.total + right.pref);
	ans.suf = max(right.suf, right.total + left.suf);
	ans.total = left.total + right.total;
	ans.mss = max(left.mss, max(right.mss, left.suf + right.pref));
	
	return ans;
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(v[l], v[l], v[l], v[l]);
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no] = merge(st[nxt], st[nxt+1]);
}

void update(int no, int l, int r, int pos, int val){
	if(pos<l || pos>r) return;
	if(l == r && l == pos){
		st[no] = node(val, val, val, val);
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = merge(st[nxt], st[nxt+1]);
}

node query(int no, int l, int r, int i, int j){
	if(j<l || i>r) return node(-INF, -INF, -INF, -INF);
	if(i<=l && r<=j) return st[no];
	
	int nxt = 2*no, mid = (l+r)/2;
	node esq, dir;
	esq = query(nxt, l, mid, i, j);
	dir = query(nxt+1, mid+1, r, i, j);
	if(esq.pref == -INF) return dir;
	if(dir.pref == -INF) return esq;
	return merge(esq, dir);
}


int main ()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	build(1, 0, n-1);
	int q, l, r, pos, val, op;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> op;
		if(op){
			cin >> l >> r;
			l--; r--;
			cout << query(1, 0, n-1, l, r).mss << "\n";
		}else{
			cin >> pos >> val;
			pos--;
			update(1, 0, n-1, pos, val);
		}
	}
	
	
	
	return 0;
}
