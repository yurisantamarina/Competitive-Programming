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
#define off 3200
set<int> s;
int n;
vector<pair<int, char> > v;

char dp[40][40][2*off];
int ans = 0;
char visto[2*off];

void solve(int pos, int aberto, int sum){
	if(pos==n){
		//~ cout << "sum = " << sum << endl;
		if(!visto[sum]){
			ans++;
			visto[sum] = 1;
		}
		return;
	}
	//~ if(sum < 0) oioi;
	if(dp[pos][aberto][sum]) return;
	dp[pos][aberto][sum] = 1;
	
	int nw;
	if(aberto%2!=0){
		if(v[pos].S=='-'){
			nw = v[pos].F + sum;
		}else{
			nw = -v[pos].F + sum;
		}
	}else{
		if(v[pos].S=='-'){
			nw = -v[pos].F + sum;
		}else{
			nw = v[pos].F + sum;
		}
	}
	if(v[pos].S == '-'){
		solve(pos+1, aberto-1 >= 0 ? aberto - 1 : aberto, nw);
		solve(pos+1, aberto+1, nw);
		solve(pos+1, aberto, nw);
	}else{
		solve(pos+1, aberto-1 >= 0 ? aberto - 1 : aberto, nw);
		solve(pos+1, aberto, nw);
	}
}


int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string ent;
	while (getline(cin, ent))
	{
		s.clear();
		stringstream ss;
		ent = "+ " + ent;
		ss << ent;
		char sinal;
		int val;
		v.clear();
		while (ss >> sinal)
		{
			ss >> val;
			v.pb(mp(val, sinal));
		}
		n = v.size();
		//~ for (int i = 0; i < v.size(); i++)
		//~ {
			//~ cout << v[i].F << " " << char(v[i].S) << endl;
		//~ }
		memset(dp, 0, sizeof dp);
		ans = 0;
		memset(visto, 0, sizeof visto);
		solve(0, 0, off);
		cout << ans << "\n";
	}
	
	
	
	return 0;
}
