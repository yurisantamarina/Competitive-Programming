#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 1000010

map<int, int> mapa;
set<int> s;
vector<int> v;
int st[4*MAXN];
int dp[MAXN];

void update(int no, int l, int r, int pos, int val){
	if(pos<l || pos>r) return;
	if(pos==l && l==r){
		st[no] = max(st[no], val);
		return;
	}
	int nxt = 2*no;
	int mid =(l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = max(st[nxt], st[nxt+1]);
}

int query(int no, int l, int r, int i, int j){
	if(i>r || j<l) return 0;
	if(i<=l && r<=j) return st[no];
	int nxt = 2*no;
	int mid =(l+r)/2;
	
	return max(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int x;
	while (cin >> x)
	{
		v.pb(x);
		s.insert(x);
	}
	
	int idx = 1;
	for(auto i : s)
		mapa[i] = idx++;
	
	for (int i = 0; i < v.size(); i++)
	{
		x = mapa[v[i]];
		dp[i] = query(1, 0, idx, 0, x-1) + 1;
		update(1, 0, idx, x, dp[i]);
	}
	
	int ans = query(1, 0, idx, 0, idx);
	vector<int> saida;
	int at = ans;
	for (int i = v.size()-1; i >= 0; i--)
	{
		if(dp[i] == at){
			at--;
			saida.pb(v[i]);
		}
	}
	cout << ans << "\n-\n";
	for (int i = saida.size()-1; i >= 0; i--)
	{
		cout << saida[i] << "\n";
	}
	
	
	
	
	
	return 0;
}
