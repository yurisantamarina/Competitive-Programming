#include <bits/stdc++.h>
using namespace std;
#define MAXN 101010

struct node{
	int sum, l, r;
	node(){}
	node(int a, int b, int c){
		sum = a;
		l = b;
		r = c;
	}
};

int root[MAXN];
int v[MAXN];
node st[10101010];
int cnt = 0;
int n;

int build(int l, int r){
	int clone = cnt++;
	if(l==r){
		st[clone] = node(v[l], 0, 0);
		return clone;
	}
	int mid = (l+r)/2;
	
	st[clone].l = build(l, mid);
	st[clone].r = build(mid+1, r);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

int query(int no, int l, int r, int i, int j){
	if(r < i || l > j) return 0;
	if(i<=l && r<=j) return st[no].sum;
	
	int mid = (l+r)/2;
	
	return query(st[no].l, l, mid, i, j) + query(st[no].r, mid+1, r, 
	i, j);
}

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	int clone = cnt++;
	st[clone] = st[no];
	if(l == r){
		st[clone].sum = val;
		return clone;
	}
	
	int mid = (l+r)/2;
	
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc, q, l, r, k, op, pos, val;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		
		cnt = 0;
		root[0] = build(0, n-1);
		cin >> q;
		
		int at = 1;
		for (int i = 0; i < q; i++)
		{
			cin >> op;
			if(op == 1){
				cin >> l >> r >> k;
				l--; r--;
				cout << query(root[k], 0, n-1, l, r) << "\n";
			}else{
				cin >> pos >> val;
				pos--;
				root[at] = update(root[at-1], 0, n-1, pos, val);
				at++;
			}
		}
	}
	
	
	return 0;
}
