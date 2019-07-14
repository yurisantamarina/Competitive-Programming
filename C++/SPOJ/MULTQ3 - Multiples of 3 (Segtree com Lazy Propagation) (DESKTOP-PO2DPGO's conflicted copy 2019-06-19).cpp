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
	int zero, um, dois;
	node(){}
	node(int a, int b, int c){
		zero = a;
		um = b;
		dois = c;
	}
	node const operator + (const node a){
		return node(zero + a.zero, um + a.um, dois + a.dois);
	}
};

node st[4*MAXN];
int lazy[4*MAXN];

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(1, 0, 0);
		lazy[no] = 0;
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no] = st[nxt] + st[nxt+1];
	lazy[no] = 0;
}

void shift(int no, int qtd){
	int aux;
	for (int i = 0; i < qtd; i++)
	{
		aux = st[no].zero;
		st[no].zero = st[no].dois;
		st[no].dois = st[no].um;
		st[no].um = aux;
	}
}

void update(int no, int l, int r, int i, int j){
	int nxt = 2*no;
	if(lazy[no]){
		shift(no, lazy[no]%3);
		if(l!=r){
			lazy[nxt] += lazy[no];
			lazy[nxt+1] += lazy[no];
		}
		lazy[no] = 0;
	}
	
	if(j<l || i>r) return;
	if(i<=l && r<=j){
		shift(no, 1);
		if(l!=r){
			lazy[nxt]++;
			lazy[nxt+1]++;
		}
		return;
	}
	
	int mid = (l+r)/2;
	update(nxt, l, mid, i, j);
	update(nxt+1, mid+1, r, i, j);
	st[no] = st[nxt] + st[nxt+1];
}

node query(int no, int l, int r, int i, int j){
	int nxt = 2*no;
	if(lazy[no]){
		shift(no, lazy[no]%3);
		if(l!=r){
			lazy[nxt] += lazy[no];
			lazy[nxt+1] += lazy[no];
		}
		lazy[no] = 0;
	}
	
	if(j<l || i>r) return node(0, 0, 0);
	if(i<=l && r<=j) return st[no];
	int mid = (l+r)/2;
	
	return query(nxt, l, mid, i, j) + query(nxt+1, mid+1, r, i, j);
}

int main ()
{
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int n, q, op, l, r;
	cin >> n >> q;
	build(1, 0, n-1);
	for (int i = 0; i < q; i++)
	{
		cin >> op >> l >> r;
		if(op==0){
			update(1, 0, n-1, l, r);
		}else{
			cout << query(1, 0, n-1, l, r).zero << "\n";
		}
	}
	
	
	return 0;
}
