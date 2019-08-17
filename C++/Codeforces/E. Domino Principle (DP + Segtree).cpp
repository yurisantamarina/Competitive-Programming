#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const ll MOD = 1000000007LL;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 305010

pair<int, pair<int, int> > v[100010];
int dp[100010];
int ans[100010];
int stMax[4*MAXN];
int stSum[4*MAXN];

void updateMax(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(pos==l && l==r){
		stMax[no] = val;
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	updateMax(nxt, l, mid, pos, val);
	updateMax(nxt+1, mid+1, r, pos, val);
	stMax[no] = max(stMax[nxt], stMax[nxt+1]);
}

int queryMax(int no, int l, int r, int i, int j){
	if(l>j || r<i) return 0;
	if(i<=l && r<=j) return stMax[no];
	int mid = (l+r)/2;
	int nxt = 2*no;
	
	return max(queryMax(nxt, l, mid, i, j), queryMax(nxt+1, mid+1, r, i, j));
}

void updateSum(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(pos==l && l==r){
		stSum[no] = val;
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	updateSum(nxt, l, mid, pos, val);
	updateSum(nxt+1, mid+1, r, pos, val);
	stSum[no] = stSum[nxt] + stSum[nxt+1];
}

int querySum(int no, int l, int r, int i, int j){
	if(l>j || r<i) return 0;
	if(i<=l && r<=j) return stSum[no];
	int mid = (l+r)/2;
	int nxt = 2*no;
	
	return querySum(nxt, l, mid, i, j) + querySum(nxt+1, mid+1, r, i, j);
}

bool compare(pair<int, pair<int, int> > a, pair<int, pair<int, int> > b){
	return a.S.F < b.S.F;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	map<int, int> mapa;
	set<int> s;
	cin >> n;
	
	int id;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i].S.F >> v[i].S.S;
		v[i].F = i;
		s.insert(v[i].S.F);
		s.insert(v[i].S.S);
		s.insert(v[i].S.F + v[i].S.S - 1);
	}
	int idx = 2;
	for(auto i : s){
		mapa[i] = idx++;
		//~ cout << "mapa " << i << " = " << idx-1 << endl;
	}
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ v[i].S.F = mapa[v[i].S.F];
		//~ v[i].S.S = mapa[v[i].S.S];
	//~ }
	
	sort(v, v+n, compare);
	int mx;
	for (int i = n-1; i >= 0; i--)
	{
		mx = max(mapa[v[i].S.F + v[i].S.S - 1], queryMax(1, 0, MAXN-1, mapa[v[i].S.F], mapa[v[i].S.F + v[i].S.S - 1]));
		updateMax(1, 0, MAXN-1, mapa[v[i].S.F], mx);
		
		id = v[i].F;
		dp[i] = querySum(1, 0, MAXN-1, mapa[v[i].S.F], mx) + 1;
		updateSum(1, 0, MAXN-1, mapa[v[i].S.F], 1);
		ans[id] = dp[i];
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
	
	
	
	
	
	return 0;
}
