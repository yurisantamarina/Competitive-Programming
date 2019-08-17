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
ll MOD = 1000000007;

ll dp[2010][2][2010];
string s;
int m, dig;

ll solve(int pos, bool bate, int mod){
	if(pos==s.size()) return !mod;
	if(dp[pos][bate][mod]!=-1) return dp[pos][bate][mod];
	
	ll ans = 0LL;
	if(bate){
		if(pos%2==0){
			if(dig <= s[pos]-'0'){
				ans += solve(pos+1, dig==s[pos]-'0' ? true : false, (mod*10 + dig)%m);
				ans%=MOD;
			}
		}else{
			for (int i = 0; i <= s[pos]-'0'; i++)
			{
				//~ if(i==dig && pos%2) continue;
				if(i==dig) continue;
				//~ if(pos%2==0){
					//~ continue;
				//~ }
				if(i==s[pos]-'0'){
					ans += solve(pos+1, true, (mod*10 + i)%m);
					ans%=MOD;
				}else{
					ans += solve(pos+1, false, (mod*10 + i)%m);
					ans%=MOD;
				}
			}
		}
		
		
	}else{
		if(pos%2==0){
			ans += solve(pos+1, false, (mod*10 + dig)%m);
			ans%=MOD;
		}else{
			for (int i = 0; i < 10; i++)
			{
				if(i==dig) continue;
				//~ if(i==dig && pos%2) continue;
				ans += solve(pos+1, false, (mod*10 + i)%m);
				ans%=MOD;
			}
		}
		
		
	}
	
	return dp[pos][bate][mod] = ans;
}

bool ok(string n){
	n.insert(n.begin(), '-');
	int mod=0;
	for (int i = 1; i < n.size(); i++)
	{
		if(i%2!=0 && n[i]-'0'==dig) return false;
		if(i%2==0 && n[i]-'0' != dig) return false;
		mod = (mod*10 + n[i]-'0')%m;
	}
	
	return !mod;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> m >> dig;
	string l, r;
	cin >> l >> r;
	
	s = "-" + l;
	//~ printf("s=%s\n", s.c_str());
	memset(dp, -1, sizeof dp);
	ll ansL = solve(1, true, 0);
	
	s = "-" + r;
	//~ printf("s=%s\n", s.c_str());
	memset(dp, -1, sizeof dp);
	ll ansR = solve(1, true, 0);
	
	ll bota = ok(l);
	//~ printf("ansL = %lld  ansR = %lld  bota = %lld\n", ansL, ansR, bota);
	cout << (ansR + MOD + MOD + bota - ansL)%MOD << "\n";
	
	return 0;
}
