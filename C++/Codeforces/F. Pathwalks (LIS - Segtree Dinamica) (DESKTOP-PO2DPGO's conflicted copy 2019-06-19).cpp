#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define INF

struct node{
	node *l, *r;
	int val;
	node(){
		l = r = NULL;
		val = 0;
	}
	node(node* a, node* b, int c){
		l = a;
		r = b;
		val = c;
	}
};

node *root[MAXN];

int merge(node *a, node *b){
	int x = 0, y = 0;
	if(a) x = a->val;
	if(b) y = b->val;
	return max(x, y);
}

void update(node *no, int l, int r, int pos, int val){
	//~ cout << "l = " << l << "  r = " << r << endl;
	if(l == r && pos == l){
		//~ cout << "oi\n";
		no->val = max(no->val, val);
		return;
	}
	
	
	int mid = (l+r)/2;
	
	if(pos <= mid){
		if(!no->l) no->l = new node();
		update(no->l, l, mid, pos, val);
	}else{
		if(!no->r) no->r = new node();
		update(no->r, mid+1, r, pos, val);
	}
	no->val = merge(no->l, no->r);
}

int query(node *no, int l, int r, int i, int j){
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return no->val;
	int mid = (l+r)/2;
	
	int x = 0, y = 0;
	if(no->l) x = query(no->l, l, mid, i, j);
	if(no->r) y = query(no->r, mid+1, r, i, j);
	
	return max(x, y);
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int n, m, u, v, w, tmp, ans = 0;
	//~ cin >> n >> m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++)
		root[i] = new node();
	
	for (int i = 0; i < m; i++)
	{
		//~ cin >> u >> v >> w;
		scanf("%d %d %d", &u, &v, &w);
		tmp = 1 + query(root[u], 0, MAXN-1, 0, w-1);
		ans = max(ans, tmp);
		update(root[v], 0, MAXN-1, w, tmp);
	}
	//~ cout << ans << "\n";
	printf("%d\n", ans);
	
	return 0;
}
