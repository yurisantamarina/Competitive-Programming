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
#define MAXN 110
int v[MAXN];
map<pair<int, int>, int> dp;
int off = 40003;
int n, F;
int f[MAXN];
int positivo[MAXN];
int negativo[MAXN];

int solve(int pos, int at){
	if(pos == n) return at == F;
	if(dp.find(mp(pos, at)) != dp.end()) return dp[mp(pos, at)];
	
	int a, b;
	a = solve(pos+1, at + v[pos]);
	b = solve(pos+1, at - v[pos]);
	
	if(a) positivo[pos] = 1;
	if(b) negativo[pos] = 1;
	
	return dp[mp(pos, at)] = a || b;
}


int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> n >> F, n)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		dp.clear();
		memset(positivo, 0, sizeof positivo);
		memset(negativo, 0, sizeof negativo);
		int ans = solve(0, 0);
		//~ cout << ans << "\n";
		
		if(!ans) cout << "*\n";
		else{
			
			for (int i = 0; i < n; i++)
			{
				if(positivo[i] && negativo[i]) cout << "?";
				else if(positivo[i]) cout << "+";
				else cout << "-";
			}
			cout << "\n";
			
		}
	}
	
	
	
	
	return 0;
}
