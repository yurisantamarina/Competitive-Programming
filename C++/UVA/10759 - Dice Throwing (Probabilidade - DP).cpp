#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
//~ typedef long long int ll;
typedef unsigned long long int ll;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};

ll dp[25][500];
ll x, n;

ll solve(ll i, ll sum){
	if(i==n) return sum < x;
	if(dp[i][sum] != -1) return dp[i][sum];
	if(sum >= x) return 0;
	
	
	ll ans = 0LL;
	for (int v = 1; v <= 6; v++)
	{
		ans += solve(i+1, sum+v);
	}
	
	return dp[i][sum] = ans;
}

int main () {
	
	while (cin >> n >> x, n!=0)
	{
		memset(dp, -1, sizeof dp);
		ll num = powl(6, n) - solve(0, 0);
		if(num == powl(6, n)){
			cout << 1 << "\n";
		}else if(num==0){
			cout << 0 << "\n";
		}else{
			ll den = powl(6,n);
			//~ cout << num << " " << den << "\n";
 			cout << (num / __gcd(num, den)) << "/" << (den / __gcd(num, den)) << "\n";
		}
	}
	
	
	
	
	
	return 0;
}
