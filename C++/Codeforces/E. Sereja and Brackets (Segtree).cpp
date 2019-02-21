#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};
ll MOD = 1e9 + 7;
#define MAXN 1000010

struct node{
	int ans, o, c;
	node(){
		ans = 0;
		o = 0;
		c = 0;
	}
	
	node(int a, int b, int cc){
		ans = a;
		o = b;
		c = cc;
	}
};

string s;
node st[4*MAXN];

node merge(node a, node b){
	node resp;
	int aux = min(a.o, b.c);
	a.o -= aux;
	b.c -= aux;
	resp.ans = a.ans + b.ans + aux*2;
	resp.o = a.o + b.o;
	resp.c = a.c + b.c;
	
	return resp;
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(0, s[l]=='(', s[l]==')');
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	st[no] = merge(st[nxt], st[nxt+1]);
}

node query(int no, int l, int r, int i, int j){
	if(r<i || l>j) return node(0,0,0);
	if(i<=l && r<=j) return st[no];
	
	int nxt = 2*no;
	int mid = (l+r)/2;
	return merge(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
}

int main(){
	int l, r;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> s;
	build(1, 0, s.size()-1);
	int q;
	cin >> q;
	while (q--)
	{
		cin >> l >> r;
		l--;
		r--;
		cout << query(1, 0, s.size()-1, l, r).ans << "\n";
	}
	
	return 0;
}
