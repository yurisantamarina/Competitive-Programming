#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define MAXN 1000000
#define mp make_pair
#define pb push_back

pair<int, int> st[MAXN][20];
int v[MAXN];
int pref[MAXN];
int suf[MAXN];
int n, q;

pair<int, int> merge(pair<int, int> a, pair<int, int> b){
	if(a.F >= b.F) return a;
	return b;
}

void build(){
	for (int i = 0; i < n; i++)
	{
		st[i][0] = mp(v[i], i);
	}
	
	for (int j = 1; j < 20; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if(i + (1<<j) - 1 >= n) break;
			st[i][j] = merge(st[i][j-1], st[i + (1<<(j-1))][j-1]);
		}
	}
	
	for (int i = 0, j = n-1; i < n; i++, j--)
	{
		if(i == 0) pref[i] = 1;
		else{
			if(v[i] >= v[i-1]) pref[i] = pref[i-1] + 1;
			else pref[i] = 1;
		}
		
		if(j == n-1) suf[j] = 1;
		else{
			if(v[j] >= v[j+1]) suf[j] = suf[j+1] + 1;
			else suf[j] = 1;
		}
	}
}

pair<int, int> query(int l, int r){
	int k = r-l+1;
	k = 31 - __builtin_clz(k);
	return merge(st[l][k], st[r - (1<<k) + 1][k]);
}

bool ok(int l, int r){
	if(l == r) return true;
	int pos = query(l, r).S;
	if(pos == l) return suf[l+1] - suf[r] == r - (l + 1);
	if(pos == r) return pref[r-1] - pref[l] == (r-1) - l;
	
	return pref[pos-1] - pref[l] == (pos-1) - l && suf[pos+1] - suf[r] == r - (pos+1);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	build();
	
	int l, r;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		l--; r--;
		if(ok(l, r)) cout << "Yes\n";
		else cout << "No\n";
	}
	
	
	
	
	
	return 0;
}
