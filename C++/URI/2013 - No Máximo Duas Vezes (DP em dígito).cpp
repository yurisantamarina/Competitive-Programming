#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
const ll MOD = 0;
const ll N = 0;

ll pot[20];
string s;
ll dp[19][2][1<<20];

bool pode(int mask, int dig){
	if((mask & (1<<dig)) && (mask & (1<<(dig+10)))) return false;
	return true;
}

int newMask(int mask, int dig){
	if(dig==0 && mask==0) return mask;
	
	if(mask & (1<<dig))
		return mask | (1<<(dig+10));
	
	return mask | (1<<dig);
}

ll solve(int pos, bool bate, int mask){
	if(pos==s.size()) return 0LL;
	if(dp[pos][bate][mask]!=-1) return dp[pos][bate][mask];
	
	ll ans = -10LL - 1e18;
	if(bate){
		
		for (int i = 0; i <= s[pos]-'0'; i++)
		{
			if(pode(mask, i)) 
				ans = max(ans, pot[s.size()-pos-1] * i + solve(pos+1, i==s[pos]-'0' ? true : false, newMask(mask, i)));
		}
	}else{
		for (int i = 0; i < 10; i++)
		{
			if(pode(mask, i))
				ans = max(ans, pot[s.size()-pos-1] * i + solve(pos+1, false, newMask(mask, i)));
		}
	}
	
	return dp[pos][bate][mask] = ans;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	pot[0] = 1LL;
	for (int i = 1; i < 20; i++)
	{
		pot[i] = pot[i-1]*10LL;
	}
	
	cin >> s;
	memset(dp, -1, sizeof dp);
	cout << solve(0, true, 0) << "\n";
	
	return 0;
}
