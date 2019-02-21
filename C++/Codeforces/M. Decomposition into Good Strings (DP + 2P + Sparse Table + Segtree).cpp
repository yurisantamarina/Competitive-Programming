#include <bits/stdc++.h>

using namespace std;
#define MAXN 200010
#define INF 1e9
#define LOG 18

struct SEGTREE{
	vector<int> st;
	SEGTREE(){
		st.resize(MAXN*4, INF);
	}
	
	void update(int no, int l, int r, int pos, int val){
		if(pos < l || pos > r) return;
		if(l==r){
			st[no] = val;
			return;
		}
		int nxt = 2*no, mid = (l+r)/2;
		update(nxt, l, mid, pos, val);
		update(nxt+1, mid+1, r, pos, val);
		st[no] = min(st[nxt], st[nxt+1]);
	}
	
	int query(int no, int l, int r, int i, int j){
		if(r < i || l > j) return INF;
		if(i <= l && r <= j) return st[no];
		int nxt = 2*no, mid = (l+r)/2;
		return min(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
	}
};

int vet[MAXN];
int dp[MAXN];

struct SPARSETABLE{
	vector<int> st[MAXN];
	int sz;
	SPARSETABLE(){}
	
	void build(int _sz){
		sz = _sz;
		for (int i = 1; i <= sz; i++){
			st[i].resize(LOG);
			st[i][0] = (1<<vet[i]);
		}
		
		for (int j = 1; j < LOG; j++)
			for (int i = 1; i + (1<<j) - 1 <= sz; i++)
				st[i][j] = st[i][j-1] | st[i + (1<<(j-1))][j-1];
	}
	
	int query(int l, int r){
		int k = 31 - __builtin_clz(r-l+1);
		return __builtin_popcount(st[l][k] | st[r - (1<<k) + 1][k]);
	}
};

int k, L, R;
SEGTREE seg;
SPARSETABLE spt;

bool ajustaL(int i){
	
	if(spt.query(L+1, i) < k) return false;
	
	while (L < i && spt.query(L+1, i) > k)
		L++;
	
	return true;
}

bool ajustaR(int i){
	if(spt.query(R+1, i) < k) return true;
	
	while (R < i && spt.query(R+1, i) >= k)
		R++;
	
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	
	cin >> k;
	cin >> s;
	int n = (int)s.size();
	
	for (int i = 0; i < n; i++)
	{
		vet[i+1] = s[i]-'a';
	}
	L = 0; R = 0;
	spt.build(n);
	
	seg.update(1, 0, n, 0, 0);
	for (int i = 1; i <= n; i++)
	{
		if(ajustaL(i) && ajustaR(i)){
			dp[i] = seg.query(1, 0, n, L, R-1) + 1;
		}else dp[i] = INF;
		
		cout << (dp[i] >= INF ? -1 : dp[i])  << " ";
		seg.update(1, 0, n, i, dp[i]);
	}
	cout << "\n";
	
	
	
	return 0;
}
