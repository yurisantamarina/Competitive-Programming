#include <bits/stdc++.h>

using namespace std;
#define MAXN 100010
#define F first
#define S second

int st[4*MAXN];
int lazy[4*MAXN];
vector<pair<int, pair<int, int> > > v;

int NEUTRO = (1<<30)-1;

void propagate(int no, int l, int r){
	if(!lazy[no]) return;

	int nxt = 2*no;
	st[no] |= lazy[no];
	
	if(l != r){
		lazy[nxt] |= lazy[no];
		lazy[nxt+1] |= lazy[no];
	}
	
	lazy[no] = 0;
	
}

void update(int no, int l, int r, int i, int j, int val){
	propagate(no, l, r);
	
	if(r < i || l > j) return;
	if(i <= l && r <= j){
		lazy[no] |= val;
		propagate(no, l, r);
		return;
	}
	
	int nxt = 2*no, mid = (l+r)/2;
	update(nxt, l, mid, i, j, val);
	update(nxt+1, mid+1, r, i, j, val);
	
	st[no] = st[nxt] & st[nxt+1];
}

int query(int no, int l, int r, int i, int j){
	propagate(no, l, r);
	if(r < i || l > j) return NEUTRO;
	if(i <= l && r <= j) return st[no];
	
	int nxt = 2*no, mid = (l+r)/2;
	
	return query(nxt, l, mid, i, j) & query(nxt+1, mid+1, r, i, j);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q, l, r, a;
	cin >> n >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r >> a;
		l--; r--;
		update(1, 0, n-1, l, r, a);
		v.push_back({a, {l, r}});
	}
	
	for (int i = 0; i < q; i++)
	{
		l = v[i].S.F;
		r = v[i].S.S;
		a = v[i].F;
		if(query(1, 0, n-1, l, r) != a){
			cout << "NO\n";
			return 0;
		}
	}
	
	cout << "YES\n";
	for (int i = 0; i < n; i++)
	{
		cout << query(1, 0, n-1, i, i) << " ";
	}
	cout << "\n";
	
	
	
	return 0;
}
