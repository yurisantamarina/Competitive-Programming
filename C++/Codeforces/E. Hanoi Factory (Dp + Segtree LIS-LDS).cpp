#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 200100

struct anel{
	int a, b, h;
	anel(){}
	anel(int x, int y, int x){
		a = x;
		b = y;
		h = z;
	}
};

anel v[MAXN];
ll dp[MAXN];
ll st[4*MAXN];
set<int> s;
map<int, int> mapa;
int cnt=1;
int n;

bool compare(anel& A, anel& B){
	if(A.b==B.b) return A.a > B.a;
	return A.b > B.b;
}

void update(int no, int l, int r, int pos, ll val){
	if(pos<l || pos>r) return;
	if(pos==l && l==r){
		st[no] = max(st[no], val);
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = max(st[nxt], st[nxt+1]);
}

ll query(int no, int l, int r, int i, int j){
	if(i>r || j<l) return 0LL;
	if(i<=l && r<=j) return st[no];
	int nxt = 2*no;
	int mid = (l+r)/2;
	
	return max(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
}

int main(){
	cin >> n;
	int a, b, h;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b >> h;
		v[i].a = a;
		v[i].b = b;
		v[i].h = h;
		s.insert(a);
		s.insert(b);
	}
	
	for(auto i : s){
		mapa[i] = cnt++;
	}
	
	sort(v, v+n, compare);
	
	memset(st, 0, sizeof st);
	ll ans = 0LL;
	for (int i = 0; i < n; i++)
	{
		a = mapa[v[i].a];
		b = mapa[v[i].b];
		ll q = query(1, 0, cnt, 0, b-1);
		dp[i] = q + v[i].h;
		ans = max(ans, dp[i]);
		update(1, 0, cnt, a, dp[i]);
	}
	
	cout << ans << "\n";
	
	
	
	return 0;
}
