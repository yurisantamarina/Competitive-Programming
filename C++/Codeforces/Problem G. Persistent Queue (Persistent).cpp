//~ http://codeforces.com/gym/100431/attachments

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010

struct node{
	int val, l, r;
	node(){}
};

node st[10101010];
int nxt = 1;
int version;
int root[201010];
int ini[201010];
int len[201010];

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	int clone = nxt++;
	st[clone] = st[nxt];
	
	if(pos == l && l == r){
		st[clone].val = val;
		return clone;
	}
	
	int mid = (l+r)/2;
	st[clone].l = update(st[no].l, l, mid, pos, val);
	st[clone].r = update(st[no].r, mid+1, r, pos, val);
	
	return clone;
}

void query(int no, int l, int r, int pos){
	if(pos < l || pos > r) return;
	if(l == r && pos == l){
		cout << st[no].val << "\n";
		return;
	}
	int mid = (l+r)/2;
	query(st[no].l, l, mid, pos);
	query(st[no].r, mid + 1, r, pos);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	root[0] = 0;
	version = 1;
	ini[0] = 0;
	len[0] = 0;
	
	int n, op, v, val;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> op;
		if(op == 1){
			cin >> v >> val;
			root[version] = update(root[v], 0, MAXN-1, len[v] + ini[v], val);
			len[version] = len[v] + 1;
			ini[version] = ini[v];
			version++;
		}else{
			cin >> v;
			query(root[v], 0, MAXN-1, ini[v]);
			root[version] = root[v];
			len[version] = len[v] - 1;
			ini[version] = ini[v] + 1;
			version++;
		}
	}
	
	
	return 0;
}
