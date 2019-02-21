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
typedef pair<ll, ll> pii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

int n, m;
struct city{
	string nome, os;
	ll val;
	city(){}
	city(string s, string o, ll v){
		nome = s;
		os = o;
		val = v;
	}
};

city esq[1010];
city dir[1010];

pair<ll, ll> dp[1010][1010];

void reset(){
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			dp[i][j].F = -1;
			dp[i][j].S = -1;
		}
	}
}

pii operator + (pii a, pii b){
	return mp(a.F + b.F, a.S + b.S);
}

pii max_(pii a, pii b){
	if(a.F == b.F) return mp(a.F, min(a.S, b.S));
	if(a.F > b.F) return a;
	return b;
}

pii solve(int l, int r){
	if(l==n || r==m) return pii(0, 0);
	if(dp[l][r].F != -1) return dp[l][r];
	
	pii ans;
	
	ans = max_(solve(l+1, r), solve(l, r+1));
	
	if(esq[l].os == dir[r].os){
		ans = max_(ans, mp(esq[l].val + dir[r].val, 1) + solve(l+1, r+1));
	}
	
	
	return dp[l][r] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	string name, os;
	int val;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> name >> os >> val;
			esq[i] = city(name, os, val);
		}
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			cin >> name >> os >> val;
			dir[i] = city(name, os, val);
		}
		reset();
		pii ans = solve(0, 0);
		cout << ans.F << " " << ans.S << "\n";
	}
	
		
	return 0;
}
