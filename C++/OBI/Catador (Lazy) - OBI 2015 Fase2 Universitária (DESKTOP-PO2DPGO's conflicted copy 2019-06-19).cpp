#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
#define ll long long int

int n, q;
int v[100010];
int st[400010];
int lazy[400010];

void update(int no, int l, int r, int i, int j, int val){
	int nxt = 2*no;
	if(lazy[nxt]){
		st[no] += lazy[no]*(r-l+1);
		if(l!=r){
			lazy[nxt] += lazy[no];
			lazy[nxt+1] += lazy[no];
		}
		lazy[no] = 0;
	}
	
	if(j<l || i>r) return;
	
	if(i<=l && r<=j){
		st[no] += val;
		if(l!=r){
			lazy[nxt] += val;
			lazy[nxt+1] += val;
		}
		return;
	}
	
	int mid = (l+r)/2;
	update(nxt, l, mid, i, j, val);
	update(nxt+1, mid+1, r, i, j, val);
}

ll query(int no, int l, int r, int i, int j){
	int nxt = 2*no;
	if(lazy[no]){
		st[no] += lazy[no] * (r-l+1);
		if(l!=r){
			lazy[nxt] += lazy[no];
			lazy[nxt+1] += lazy[no];
		}
		lazy[no] = 0;
	}
	
	if(j<l || i>r) return 0LL;
	if(i<=l && r<=j) return st[no];
	
	int mid = (l+r)/2;
	return query(nxt, l, mid, i, j) + query(nxt+1, mid+1, r, i, j);
}

int main () {
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	memset(st, 0, sizeof st);
	memset(lazy, 0, sizeof lazy);
	int idx;
	for (int i = 0; i < q; i++)
	{
		cin >> idx; idx--;
		int val = max(0LL, v[idx] - query(1, 0, n-1, idx, idx));
		//~ cout << "update : " << val << " " << max(0, idx-val) << ", " << min(n-1, idx+val) << endl;
		update(1, 0, n-1, max(0, idx-val), min(n-1, idx+val), 1);
	}
	
	ll ans = 0LL;
	for (int i = 0; i < n; i++)
	{
		ans += max(0LL, v[i] - query(1, 0, n-1, i, i));
	}
	
	cout << ans << "\n";
	
	
	
	
	
	return 0;
}
