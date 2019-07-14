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

int dp[1<<10][10000];
char memo[1<<10][10000];
int d;
string s;
int sz;
int fat[12];

int solve(int mask, int resto){
	if(mask == (1<<sz)-1) return !resto;
	if(memo[mask][resto]) return dp[mask][resto];
	memo[mask][resto] = 1;
	
	int ans=0;
	for (int i = 0; i < sz; i++)
	{
		if(mask & (1<<i)) continue;
		ans += solve(mask | (1<<i), (resto*10 + s[i]-'0')%d);
	}
	
	
	return dp[mask][resto]=ans;
}

int func(){
	int cnt[12];
	memset(cnt, 0, sizeof cnt);
	for (int i = 0; i < sz; i++)
	{
		cnt[s[i]-'0']++;
	}
	int ans = 1;
	for (int i = 0; i < 10; i++)
	{
		ans *= fat[cnt[i]];
	}
	
	return ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	cin >> tc;
	
	fat[0] = 1;
	for (int i = 1; i < 11; i++)
	{
		fat[i] = fat[i-1]*i;
	}
	
	while (tc--)
	{
		cin >> s >> d;
		memset(memo, 0, sizeof memo);
		sz = (int)s.size();
		cout << solve(0, 0)/func() << "\n";
	}
	
		
	return 0;
}
