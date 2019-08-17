#include <bits/stdc++.h>

using namespace std;
#define MAXN 500010

int n, v[MAXN], st[4*MAXN];

void build(int no, int l, int r){
	if(l == r){
		st[no] = v[l];
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no] = __gcd(st[nxt], st[nxt+1]);
}

void update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(pos == l && l == r){
		st[no] = val;
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	
	st[no] = __gcd(st[nxt], st[nxt+1]);
}

int mudou = false;

bool check(int no, int l, int r, int i, int j, int x){
	if(l == r) return true;
	
	int nxt = 2*no, mid = (l+r)/2;
	if(st[nxt] % x != 0 && st[nxt+1] % x != 0) return false;
	if(st[nxt] % x != 0 && st[nxt+1] % x == 0) return check(nxt, l, mid, i, j, x);
	if(st[nxt] % x == 0 && st[nxt+1] % x != 0) return check(nxt+1, mid+1, r, i, j, x);
	return true;
}

bool query(int no, int l, int r, int i, int j, int x){
	if(r < i || l > j) return true;
	if(i <= l && r <= j){
		if(st[no] % x == 0) return true;
		if(mudou) return false;
		if(check(no, l, r, i, j, x)){
			mudou = true;
			return true;
		}
		return false;
	}
	int nxt = 2*no, mid = (l+r)/2;
	bool esq = query(nxt, l, mid, i, j, x);
	bool dir = query(nxt+1, mid+1, r, i, j, x);
	return esq && dir;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	build(1, 0, n-1);
	
	int q, x, pos, l, r, val, op;
	cin >> q;
	
	while (q--)
	{
		cin >> op;
		mudou = false;
		if(op == 1){
			cin >> l >> r >> x;
			if(query(1, 0, n-1, l-1, r-1, x)) cout << "YES\n";
			else cout << "NO\n";
		}else{
			cin >> pos >> val;
			update(1, 0, n-1, pos-1, val);
		}
	}
	
	
	return 0;
}
