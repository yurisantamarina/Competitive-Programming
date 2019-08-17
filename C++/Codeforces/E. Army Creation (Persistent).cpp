#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010

struct node{
	int sum, l, r;
};

node st[10101010];
int v[MAXN], root[MAXN];
queue<int> Q[MAXN];
int nxt = 1;

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	int clone = nxt++;
	st[clone] = st[no];
	
	if(l == r){
		st[clone].sum += val;
		return clone;
	}
	
	int mid = (l+r)/2;
	
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

int query(int no, int l, int r, int i, int j){
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return st[no].sum;
	
	int mid = (l+r)/2;
	
	return query(st[no].l, l, mid, i, j) + query(st[no].r, mid+1, r, i, j);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, k, q;
	
	cin >> n >> k;
	
	root[0] = 0;
	for (int i = 1; i <= n; i++){
		cin >> v[i];
		root[i] = update(root[i-1], 1, MAXN-1, i, 1);
		if(Q[v[i]].size() == k){
			root[i] = update(root[i], 1, MAXN-1, Q[v[i]].front(), -1);
			Q[v[i]].pop();
			
		}
		Q[v[i]].push(i);
	}
	
	int l, r;
	cin >> q;
	int lst = 0;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		l = (l + lst)%n + 1;
		r = (r + lst)%n + 1;
		if(l > r) swap(l, r);
		
		cout << (lst = query(root[r], 1, MAXN-1, l, r))  << "\n";
	}
	
	
	
	return 0;
}
