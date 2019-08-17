//~ http://codeforces.com/gym/101252/problem/F

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

#define MAXN 1000010

int st[4*MAXN];
int dp[100010];
int v[100010];

int query(int no, int l, int r, int i, int j){
	if(r<i || l>j) return 0;
	if(i<=l && r<=j) return st[no];
	int mid = (l+r)/2;
	int nxt = 2*no;
	return max(query(nxt, l, mid, i, j), query(nxt+1, mid+1, r, i, j));
}

void update(int no, int l, int r, int pos, int val){
	if(pos< l || pos > r) return;
	if(pos==l && l==r){
		st[no] = max(st[no], val);
		return;
	}
	int mid = (l+r)/2;
	int nxt = 2*no;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = max(st[nxt], st[nxt+1]);
}

int getMax(int l, int r){
	if(l<0) return 0;
	return query(1, 0, MAXN-1, l, r);
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		dp[i] = max(getMax(0, v[i]-2), max(getMax(v[i], v[i]), getMax(v[i]+2, MAXN-1))) + 1;
		//~ cout << dp[i] << " ";
		update(1, 0, MAXN-1, v[i], dp[i]);
		ans = max(ans, dp[i]);
	}
	//~ cout << endl;
	int lst = 1e7;
	int val = ans;
	vector<int> saida;
	//~ printf("MAXIMO = %d\n", ans);
	for (int i = n-1; i >= 0; i--)
	{
		//~ cout << dp[i] << " ";
		if(val && dp[i]==val && abs(lst - v[i]) != 1){
			val--;
			lst = v[i];
			saida.pb(v[i]);
		}
	}
	//~ cout << endl;
	cout << n-ans << "\n";
	for (int i = saida.size()-1; i >= 0; i--)
	{
		cout << saida[i] << " ";
	}
	cout << "\n";
	
	
	
	
	
	
	
	return 0;
}
