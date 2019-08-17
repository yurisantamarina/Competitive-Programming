#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const ll dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const ll dy[] = {-1,0,0, 1,1, 1,-1,-1};
ll gcd (ll x, ll y) {return (y != 0 ? gcd (y, x%y) : x);}
ll lcm (ll x, ll y) {return (x / gcd (x, y) * y);}

string s;
int tam;
ll dp[18][2][160];

ll solve(int pos, bool bate, int sum){
	if(pos==tam) return sum;
	if(dp[pos][bate][sum]!=-1) return dp[pos][bate][sum];
	
	ll ans = 0LL;
	if(bate){
		for (int i = 0; i <= s[pos]-'0'; i++)
			ans += solve(pos+1, i==s[pos]-'0' ? true : false, sum + i);
	}else{
		for (int i = 0; i < 10; i++)
			ans += solve(pos+1, false, sum+i);
	}
	
	
	return dp[pos][bate][sum] = ans;
}

int main(){
	
	int t;
	cin >> t;
	while (t--)
	{
		ll l, r;
		cin >> l >> r;
		l--;
		
		ll ansL, ansR;
		
		s = to_string(l);
		tam = s.size();
		memset(dp, -1, sizeof dp);
		ansL = solve(0, 1, 0);
		
		s = to_string(r);
		tam = s.size();
		memset(dp, -1, sizeof dp);
		ansR = solve(0, 1, 0);
		
		cout << ansR - ansL << endl;
	}
	
	
	return 0;
}
