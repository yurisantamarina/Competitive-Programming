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
const int dx[] =  { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] =  {-1, 0,  0, 1, 1,  1, -1, -1};
const int dx2[] = { 0, 2, -2, 0, 2, -2, -2,  2};
const int dy2[] = {-2, 0,  0, 2, 2,  2, -2, -2};
const int N = 0;
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

//~ vector<pair<int, int> > blob;
//~ int mapa[17][17];
int dp[1<<16];
int n, m, k;

int get(int x, int y){
	return x*4 + y;
}

pair<int, int> getRev(int i){
	return mp(i/4, i%4);
}

bool pode(int x, int y, int i, int mask){
	if(!(x>=0 && x<n && y>=0 && y<m)) return false;
	if(!(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<m)) return false;
	
	if((mask & (1<<get(x, y))) && !(mask & (1<<get(x+dx[i], y+dy[i])))) return true;
	return false;
}

int getNewMask(int x, int y, int i, int mask){
	return ((mask & ~(1<<get(x, y))) & ~(1<<get(x+dx[i], y+dy[i]))) | (1<<get(x+2*dx[i], y+2*dy[i]));
}

int solve(int mask){
	//~ cout << __builtin_popcount(mask) << endl;
	if(__builtin_popcount(mask) == 1) return 1;
	if(dp[mask]!=-1) return dp[mask];
	
	int ans = 0;
	int x, y;
	pair<int, int> p;
	for (int pos = 0; pos < 16; pos++)
	{
		if(mask & (1 << pos)){
			p = getRev(pos);
			x = p.F;
			y = p.S;
			for (int i = 0; i < 8; i++)
			{
				if(pode(x+dx[i], y+dy[i], i, mask)){
					//~ printf("")
					ans += solve(getNewMask(x, y, i, mask));
				}
			}
			
		}
	}
	
	return dp[mask] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc;
	cin >> tc;
	int x, y, mask, caso=1;
	while (tc--)
	{
		cin >> n >> m >> k;
		//~ memset(mapa, 0, sizeof mapa);
		//~ blob.clear();
		mask = 0;
		for (int i = 0; i < k; i++)
		{
			cin >> x >> y;
			x--; y--;
			mask |= (1<<get(x, y));
		}
		memset(dp, -1, sizeof dp);
		cout << "Case " << caso++ << ": " << solve(mask) << "\n";
	}
	
		
	return 0;
}
