#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
typedef long long int ll;

struct node{
	ll sum;
	int mx;
	node(){}
	node(ll _sum, int _mx){
		sum = _sum;
		mx = _mx;
	}
};

int v[MAXN];
node st[4 * MAXN];

node merge(node &a, node &b){
	return node(a.sum + b.sum, max(a.mx, b.mx));
}

void build(int no, int l, int r){
	if(l == r){
		st[no] = node(v[l], v[l]);
		return;
	}
	int nxt = 2 * no, mid = (l + r) / 2;
	build(nxt, l, mid);
	build(nxt + 1, mid + 1, r);
	st[no] = merge(st[nxt], st[nxt + 1]);
}

void update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(l == r){
		st[no] = node(val, val);
		return;
	}
	int nxt = 2 * no, mid = (l + r) / 2;
	update(nxt, l, mid, pos, val);
	update(nxt + 1, mid + 1, r, pos, val);
	st[no] = merge(st[nxt], st[nxt + 1]);
}

ll querySum(int no, int l, int r, int i, int j){
	if(l > r || r < i || l > j || i > j) return 0;
	if(i <= l && r <= j) return st[no].sum;
	int nxt = 2 * no, mid = (l + r) / 2;
	return querySum(nxt, l, mid, i, j) + querySum(nxt + 1, mid + 1, r, i, j);
}

int n;

int queryMx(int no, int l, int r, int i, int j, ll k){
	if(r < i || l > j || l > r || i > j) return n + 1;
	if(st[no].mx < k) return n + 1;
	
	if(l == r) return l;
	int nxt = 2 * no, mid = (l + r) / 2;
	if(i <= l && r <= j){
		int mxLeft = st[nxt].mx;
		int mxRight = st[nxt + 1].mx;
		if(mxLeft >= k) return queryMx(nxt, l, mid, i, j, k);
		else if(mxRight >= k) return queryMx(nxt + 1, mid + 1, r, i, j, k);
		return n + 1;
	}
	
	int a = queryMx(nxt, l, mid, i, j, k);
	if(a == n + 1) return queryMx(nxt + 1, mid + 1, r, i, j, k);
	return a;
}

int solve(){
	int pref = 0, id;
	while(1){
		id = queryMx(1, 1, n, pref + 1, n, querySum(1, 1, n, 1, pref));
		if(id == n + 1) return -1;
		if(v[id] == querySum(1, 1, n, 1, id - 1)) return id;
		pref = id;
	}
	return -1;
}

int main(){
	int q, pos, val;
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	
	build(1, 1, n);
	
	while (q--)
	{
		scanf("%d %d", &pos, &val);
		v[pos] = val;
		update(1, 1, n, pos, val);
		printf("%d\n", solve());
	}
	
	
	return 0;
}
