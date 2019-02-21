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
 
int v[MAXN], n, q, acum[MAXN];
node st[4*MAXN];
 
void build(int no, int l, int r){
	if(l==r){
		st[no] = node(v[l], v[l], v[l], v[l]);
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	node esq = st[nxt];
	node dir = st[nxt+1];
	node at;
	
	at.pref = max(esq.pref, max(esq.total, max(esq.total + dir.pref, esq.total + dir.total)));
	at.suf = max(dir.suf, max(dir.total, max(dir.total + esq.suf, dir.total + esq.total)));
	at.total = esq.total + dir.total;
	at.mss = max(esq.mss, max(dir.mss, esq.suf + dir.pref));
	
	//~ printf("[%d, %d]: pref = %d  suf = %d  total = %d  mss = %d\n", l, r, at.pref, at.suf, at.total, at.mss);
	
	st[no] = at;
}
 
node query(int no, int l, int r, int i, int j){
	if(j < l || i > r){
		//~ cout << "totalmente fora\n";
		return node(-INF, -INF, -INF, -INF);
	}
	if(i<=l && r<=j){
		//~ cout << "totalmente dentro   ";
		//~ printf("[%d, %d]: pref = %d  suf = %d  total = %d  mss = %d\n", l, r, st[no].pref, st[no].suf, st[no].total, st[no].mss);
		return st[no];
	}
	
	
	int nxt = 2*no, mid = (l+r)/2;
	
	node esq = query(nxt, l, mid, i, j);
	node dir = query(nxt+1, mid+1, r, i, j);
	node at;
	
	if(esq.pref==-INF){
		at = dir;
	}else if(dir.pref==-INF){
		at = esq;
	}else{
		at.pref = max(esq.pref, max(esq.total, max(esq.total + dir.pref, esq.total + dir.total)));
		at.suf = max(dir.suf, max(dir.total, max(dir.total + esq.suf, dir.total + esq.total)));
		at.total = esq.total + dir.total;
		at.mss = max(esq.mss, max(dir.mss, esq.suf + dir.pref));
		//~ cout << "parcial   ";
		//~ printf("[%d, %d]: pref = %d  suf = %d  total = %d  mss = %d\n", l, r, at.pref, at.suf, at.total, at.mss);
	}
	
	return at;
}
 
int main ()
{
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> v[i];
		//~ if(i==0) acum[i] = v[i];
		//~ else acum[i] = acum[i-1] + v[i];
	}
	
	build(1, 0, n-1);
	cin >> q;
	int l, r;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		l--; r--;
		cout << query(1, 0, n-1, l, r).mss << "\n";
	}
	
	
	return 0;
}
