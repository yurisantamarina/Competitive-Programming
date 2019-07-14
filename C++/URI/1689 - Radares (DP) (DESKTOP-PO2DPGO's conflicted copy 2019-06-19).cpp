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


#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

#define MAXN 1000010
int pos[MAXN];
int cost[MAXN];
int prv[MAXN];
int dp[MAXN];
int n;

void solve(){
	dp[0] = 0;
	for (int pos = 1; pos <= n; pos++)
	{
		dp[pos] = max(dp[pos-1], cost[pos] + dp[prv[pos]]);
	}
	
}

//~ int solve(int pos){
	//~ if(pos >= n) return 0;
	
	//~ return dp[pos] = max(solve(pos+1), cost[pos] + solve(nxt[pos]));
//~ }

int main () {
	
	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	int tc,  d;
	//~ cin >> tc;
	scanint(tc);
	while (tc--)
	{
		//~ cin >> n >> d;
		scanint(n);
		scanint(d);
		for (int i = 1; i <= n; i++)
		{
			//~ cin >> pos[i];
			scanint(pos[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			//~ cin >> cost[i];
			scanint(cost[i]);
		}
		pos[0] = 1e9;
		int l = n, r = n;
		
		while (r >= 1)
		{
			if(l==0){
				prv[r] = l;
				r--;
			}else{
				if(abs(pos[l] - pos[r]) < d){
					if(l > 0){
						l--;
					}else{
						l = 0;
						prv[r] = l;
						r--;
					}
				}else{
					prv[r] = l;
					r--;
				}
			}
		}
		
		
		//~ for (int i = 1; i <= n; i++)
		//~ {
			//~ cout << prv[i] << ' ';
		//~ }
		//~ cout << endl;
		//~ memset(dp, -1, sizeof dp);
		//~ cout << solve(0) << "\n";
		solve();
		printf("%d\n", dp[n]);
		//~ cout << dp[n] << "\n";
	}
	
		
	return 0;
}
