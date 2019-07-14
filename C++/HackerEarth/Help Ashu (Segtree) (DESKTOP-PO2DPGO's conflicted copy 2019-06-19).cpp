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
	int par, impar;
	node(){}
	node(int a, int b){
		par = a;
		impar = b;
	}
	
	node operator + (node b){
		return node(par + b.par, impar + b.impar);
	}
};

node st[4*MAXN];
int v[MAXN];

bool par(int u){
	if(u%2==0) return true;
	return false;
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(par(v[l]), !par(v[l]));
		return;
	}
	int mid = (l+r)/2, nxt=2*no;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no] = st[nxt] + st[nxt+1];
}

void update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(l==r && l==pos){
		st[no] = node(par(val), !par(val));
		return;
	}
	int mid = (l+r)/2, nxt = 2*no;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	
	st[no] = st[nxt] + st[nxt+1];
}

node query(int no, int l, int r, int i, int j){
	if(j<l || i>r) return node(0, 0);
	if(i<=l && r<=j) return st[no];
	
	int mid = (l+r)/2, nxt = 2*no;
	
	return query(nxt, l, mid, i, j) + query(nxt+1, mid+1, r, i, j);
}

int main () {
	int n, q;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	build(1, 0, n-1);
	cin >> q;
	int op;
	for (int i = 0; i < q; i++)
	{
		cin >> op;
		if(op==0){
			int pos, val;
			cin >> pos >> val;
			update(1, 0, n-1, pos-1, val);
		}else{
			int l, r;
			cin >> l >> r;
			l--; r--;
			node ans = query(1, 0, n-1, l, r);
			if(op==1) cout << ans.par << "\n";
			else if(op==2) cout << ans.impar << "\n";
		}
	}
	
	
	
	
	
	
	return 0;
}
