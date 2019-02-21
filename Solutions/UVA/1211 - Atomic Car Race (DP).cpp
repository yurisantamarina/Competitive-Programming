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

int pos[110];
double b;
int r;
double v, e, f;
double cost[10010];
double dp[110];
int n;

double getCost(int x){
	if(x >= r){
		return 1.0 / (v - e*(x-r));
	}else{
		return 1.0 / (v - f*(r-x));
	}
}

double solve(int posi){
	if(posi==n) return 0.0;
	if(dp[posi] > -0.5) return dp[posi];
	
	double ans = 10000000000.0;
	
	int x;
	for (int i = posi+1; i <= n; i++)
	{
		x = pos[i] - pos[posi];
		ans = min(ans, (posi==0 ? 0 : b) + cost[x-1] + solve(i));
	}
	
	
	
	return dp[posi] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	while (cin >> n, n)
	{
		pos[0] = 0;
		dp[0] = -1.0;
		for (int i = 1; i <= n; i++)
		{
			cin >> pos[i];
			dp[i] = -1.0;
		}
		cin >> b;
		cin >> r >> v >> e >> f;
		
		cost[0] = getCost(0);
		for (int i = 1; i <= pos[n]; i++)
		{
			cost[i] = cost[i-1] + getCost(i);
		}
		//~ for (int i = 0; i <= pos[n]; i++)
		//~ {
			//~ cout << cost[i] << " ";
		//~ }
		//~ cout << endl;
		cout << fixed << setprecision(4) << solve(0) << "\n";
	}
	
	return 0;
}
