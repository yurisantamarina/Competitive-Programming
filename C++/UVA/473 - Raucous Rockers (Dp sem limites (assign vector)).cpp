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

int n, m, t;
vector<vector<vector<int> > > dp;
int v[100000];

int solve(int song, int falta, int disco){
	if(song == n || disco == m) return 0;
	if(dp[song][falta][disco]!=-1) return dp[song][falta][disco];
	
	int ans = 0;
	
	ans = max(ans, solve(song+1, falta, disco));
	if(falta - v[song] >= 0) ans = max(ans, 1 + solve(song+1, falta - v[song], disco));
	ans = max(ans, solve(song, t, disco+1));
	
	
	return dp[song][falta][disco] = ans;
}

void reset(){
	
	//~ oioi;
	dp.clear();
	dp.assign(n+1, vector<vector<int> >());
	//~ oioi;
	//~ dp.resize(n, -1);
	for (int i = 0; i <= n; i++)
	{
		dp[i].clear();
		dp[i].assign(t+1, vector<int>());
		for (int j = 0; j <= t; j++)
		{
			dp[i][j].clear();
			dp[i][j].assign(m+1, -1);
		}
	}
	
	//~ oioi;
	//~ cout << "sz1 = " << dp.size() << endl;
	//~ cout << "sz2 = " << dp[0].size() << endl;
	//~ cout << "sz3 = " << dp[0][0].size() << endl;
	
	
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	cin >> tc;
	bool fst = true;
	while (tc--)
	{
		if(!fst) cout << "\n";
		fst = false;
		cin >> n >> t >> m;
		//~ printf("%d %d %d\n", n, t, m);
		string s;
		
		getline(cin, s);
		getline(cin, s);
		//~ cout << s << endl << endl;
		for (int i = 0; i < s.size(); i++)
		{
			if(s[i]==',') s[i] = ' ';
		}
		
		stringstream ss;
		ss << s;
		int x;
		
		for (int i = 0; ss >> x; i++)
		{
			v[i] = x;
		}
		
		reset();
		cout << solve(0, t, 0) << "\n";
	}
	
		
	return 0;
}
