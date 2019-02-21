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

string s;
ll dp[25][2][2][2];
ll n;

ll solve(int pos, bool comecou, bool bate, bool isUm){
	if(pos == s.size()) return 1;
	if(dp[pos][comecou][bate][isUm]!=-1) return dp[pos][comecou][bate][isUm];
	
	ll ans = 0;
	if(bate){
		if(comecou){
			if(isUm){
				if(s[pos]-'0' == 0){
					ans += solve(pos+1, true, true, false);//0
				}else if(s[pos]-'0' == 1){
					ans += solve(pos+1, true, true, true);//1
					ans += solve(pos+1, true, false, false);//0
				}else if(s[pos]-'0' == 2){
					ans += solve(pos+1, true, true, false);//2
					ans += solve(pos+1, true, false, true);//1
					ans += solve(pos+1, true, false, false);//0
				}else if(s[pos]-'0' == 3){
					ans += solve(pos+1, true, false, true);//1
					ans += ll(2) * solve(pos+1, true, false, false);//0 2
				}else if(s[pos]-'0' == 4){
					ans += solve(pos+1, true, false, true);//1
					ans += ll(2)*solve(pos+1, true, false, false);//0 2
				}else{
					ans += solve(pos+1, true, true, false);//5
					ans += solve(pos+1, true, false, true);//1
					ans += ll(s[pos]-'0'-3)*solve(pos+1, true, false, false);//0 2
				}
			}else{
				if(s[pos]-'0' == 0){
					ans += solve(pos+1, true, true, false);//0
				}else if(s[pos]-'0' == 1){
					ans += solve(pos+1, true, true, true);//1
					ans += solve(pos+1, true, false, false);//0
				}else if(s[pos]-'0' == 2){
					ans += solve(pos+1, true, true, false);//2
					ans += solve(pos+1, true, false, true);//1
					ans += solve(pos+1, true, false, false);//0
				}else if(s[pos]-'0' == 3){
					ans += solve(pos+1, true, true, false);//3
					ans += solve(pos+1, true, false, true);//1
					ans += ll(2) * solve(pos+1, true, false, false);//0 2
				}else if(s[pos]-'0' == 4){
					//~ ans += solve(pos+1, true, true, false);
					ans += solve(pos+1, true, false, true);//1
					ans += ll(s[pos]-'0'-1)*solve(pos+1, true, false, false);//0 2 3
				}else{
					ans += solve(pos+1, true, true, false);//5
					ans += solve(pos+1, true, false, true);//1
					ans += ll(s[pos]-'0'-2)*solve(pos+1, true, false, false);//0 2 3
				}
			}
			
			
		}else{
			if(s[pos]-'0' == 0){
				ans += solve(pos+1, false, true, false);//0
			}else if(s[pos]-'0' == 1){
				ans += solve(pos+1, true, true, true);//1
				ans += solve(pos+1, false, false, false);//0
			}else if(s[pos]-'0' == 2){
				ans += solve(pos+1, true, true, false);//2
				ans += solve(pos+1, true, false, true);//1
				ans += solve(pos+1, false, false, false);//0
			}else if(s[pos]-'0' == 3){
				ans += solve(pos+1, true, true, false);//3
				ans += solve(pos+1, true, false, true);//1
				ans += solve(pos+1, false, false, false);//0
				ans += ll(s[pos]-'0'-2)*solve(pos+1, true, false, false);//2
			}else if(s[pos]-'0' == 4){
				//~ ans += solve(pos+1, true, true, false);//3
				ans += solve(pos+1, true, false, true);//1
				ans += solve(pos+1, false, false, false);//0
				ans += ll(s[pos]-'0'-2)*solve(pos+1, true, false, false);//2 3
			}else{
				ans += solve(pos+1, true, true, false);//5
				ans += solve(pos+1, true, false, true);//1
				ans += solve(pos+1, false, false, false);//0
				ans += ll(s[pos]-'0'-3)*solve(pos+1, true, false, false);//2 3
			}
		}
	}else{
		if(comecou){
			if(isUm){
				ans = solve(pos+1, true, false, true);//1
				ans += ll(10-3)*solve(pos+1, true, false, false);//tira o 1 3 e 4
			}else{
				ans = solve(pos+1, true, false, true);//1
				ans += ll(10-2)*solve(pos+1, true, false, false);//tira o 1 e 4
			}
		}else{
			ans = solve(pos+1, true, false, true);//1
			ans += solve(pos+1, false, false, false);//0
			ans += ll(10-3)*solve(pos+1, true, false, isUm);//tira o 0 e o 1 e 4
		}
	}
	
	
	return dp[pos][comecou][bate][isUm] = ans;
}



int main () {
	
	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	while (cin >> n)
	{
		llu ans;
		llu lo = 1LLU, hi = ULLONG_MAX-1LLU, mid;
		//~ cout << mid << endl;
		while (lo <= hi)
		{
			memset(dp, -1, sizeof dp);
			mid = ((long double)lo+hi)/2LLU;
			s = to_string(mid);
			ans = solve(0, false, true, false);
			//~ if(ans == n){
				//~ lo = mid;
			//~ }
			if(ans <= n){
				lo = mid+1;
			}else{
				hi = mid-1;
			}
			
		}
		cout << lo << "\n";
	}
	
		
	return 0;
}
