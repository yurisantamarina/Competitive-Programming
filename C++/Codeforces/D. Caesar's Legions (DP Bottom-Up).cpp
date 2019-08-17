#include <bits/stdc++.h>

using namespace std;
#define MAXN 120
#define mp make_pair
#define MOD 100000000
#define FOOT 0

int dp[MAXN][MAXN][2];

int main(){
	int footmen, horsemen, k1, k2;
	cin >> footmen >> horsemen >> k1 >> k2;
	
	for (int fm = 0; fm <= footmen; fm++)
	{
		for (int hm = 0; hm <= horsemen; hm++)
		{
			for (int turn = 0; turn <= 1; turn++)
			{
				if(fm == 0 && hm == 0) dp[fm][hm][turn] = 1;
				else dp[fm][hm][turn] = 0;
				 
				if(turn == FOOT){
					for (int i = 1; hm - i >= 0 && i <= k2; i++)
					{
						dp[fm][hm][turn] += dp[fm][hm - i][turn ^ 1];
						dp[fm][hm][turn] %= MOD;
					}
				}else{
					for (int i = 1; fm - i >= 0 && i <= k1; i++)
					{
						dp[fm][hm][turn] += dp[fm - i][hm][turn ^ 1];
						dp[fm][hm][turn] %= MOD;
					}
				}
			}
		}
	}
	cout << (dp[footmen][horsemen][0] + dp[footmen][horsemen][1])%MOD << "\n";
	
	return 0;
}
