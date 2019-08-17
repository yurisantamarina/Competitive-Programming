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
typedef pair<int, int> pii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const ll MOD = 1000000007LL;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 2002

pii dp[MAXN][MAXN];
string s;
int especial[MAXN];

int cost(int l, int r){
	return especial[l] + especial[r];
}

pii operator + (pii a, pii b){
	return mp(a.F + b.F, a.S + b.S);
}

pii max_(pii a, pii b){
	if(a.F == b.F) return mp(a.F, max(a.S, b.S));
	if(a.F > b.F) return a;
	return b;
}

pii solve(int l, int r){
	if(l==r) return mp(especial[l], 1);
	if(l > r) return mp(0, 0);
	if(dp[l][r].F!=-1) return dp[l][r];
	
	pii ans = mp(-1e9, -1e9);
	
	ans = max_(solve(l+1, r), solve(l, r-1));
	if(s[l] == s[r]){
		ans = max_(ans, mp(cost(l, r), 2) + solve(l+1, r-1));
	}
	return dp[l][r] = ans;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, x;
	cin >> s;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		especial[x-1] = 1;
	}
	for (int i = 0; i < s.size(); i++)
	{
		for (int j = 0; j < s.size(); j++)
		{
			dp[i][j] = mp(-1, -1);
		}
	}
	
	cout << solve(0, s.size()-1).S << "\n";
	return 0;
}
