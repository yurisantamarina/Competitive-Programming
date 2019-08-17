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
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

char memo[281][1<<12][4];
int dp[281][1<<12][4];
int n;
int a[12];
int b[12];
int c[12];

int solve(int falta, int mask, int lst){
	if(falta < 0) return -1e9;
	if(mask == (1<<n)-1) return 0;
	if(memo[falta][mask][lst]) return dp[falta][mask][lst];
	memo[falta][mask][lst] = 1;
	
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if(mask & (1<<i)) continue;
		if(lst == 0){
			ans = max(ans, 1 + solve(falta - b[i], mask | (1<<i), 1));
			ans = max(ans, 1 + solve(falta - c[i], mask | (1<<i), 2));
		}else if(lst==1){
			ans = max(ans, 1 + solve(falta - a[i], mask | (1<<i), 0));
			ans = max(ans, 1 + solve(falta - c[i], mask | (1<<i), 2));
		}else if(lst==2){
			ans = max(ans, 1 + solve(falta - a[i], mask | (1<<i), 0));
			ans = max(ans, 1 + solve(falta - b[i], mask | (1<<i), 1));
		}else{
			ans = max(ans, 1 + solve(falta - a[i], mask | (1<<i), 0));
			ans = max(ans, 1 + solve(falta - b[i], mask | (1<<i), 1));
			ans = max(ans, 1 + solve(falta - c[i], mask | (1<<i), 2));
		} 
	}
	
	
	return dp[falta][mask][lst] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
		}
		for (int i = 0; i < n; i++)
		{
			cin >> b[i];
		}
		for (int i = 0; i < n; i++)
		{
			cin >> c[i];
		}
		memset(memo, 0, sizeof memo);
		cout << solve(280, 0, 3) << "\n";
	}
	
		
	return 0;
}
