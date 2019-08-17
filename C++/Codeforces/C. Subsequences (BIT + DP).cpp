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
#define MAXN 100010

ll bit[MAXN];
ll dp[MAXN][13];
int v[MAXN];

void update(ll pos, ll val){
	while (pos < MAXN)
	{
		bit[pos] += val;
		pos += pos & -pos;
	}
}

ll query(ll pos){
	ll ans=0LL;
	while (pos > 0)
	{
		ans += bit[pos];
		pos -= pos & -pos;
	}
	return ans;
}

int main () {
	int n, k;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n >> k;
	k++;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	
	ll ans = 0LL;
	for (int tam = 1; tam <= k; tam++)
	{
		memset(bit, 0, sizeof bit);
		for (int i = 0; i < n; i++)
		{
			if(tam==1){
				dp[i][tam] = 1LL;
			}else{
				dp[i][tam] = query(v[i]-1);
				update(v[i], dp[i][tam-1]);
			}
			if(tam==k){
				ans += dp[i][tam];
			}
		}
	}
	cout << ans << "\n";
	
	
		
	return 0;
}
