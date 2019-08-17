#include <bits/stdc++.h>

using namespace std;
#define lim 500
long double ganha, perde;
int D;
char memo[25][25][lim+1];
long double dp[25][25][lim+1];

long double solve(int EV1, int EV2, int at){
	if(EV2 <= 0) return 1.0;
	if(EV1 <= 0) return 0.0;
	if(at == lim) return EV1 > EV2;
	if(memo[EV1][EV2][at]) return dp[EV1][EV2][at];
	memo[EV1][EV2][at] = 1;
	//~ printf("EV1 = %d  EV2 = %d\n", EV1, EV2);
	long double ans = ganha * solve(EV1 + D, EV2 - D, at+1);
	ans += perde * solve(EV1 - D, EV2 + D, at+1);
	
	return dp[EV1][EV2][at] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int EV1, EV2, AT;
	while (cin >> EV1 >> EV2 >> AT >> D)
	{
		if(!EV1 && !EV2 && !AT && !D) break;
		
		ganha = 1.0*AT / 6;
		perde = 1.0 - ganha;
		memset(memo, 0, sizeof memo);
		//~ cout << "ganha = " << ganha << " perde = " << perde << endl;
		cout << fixed << setprecision(1) << solve(EV1, EV2, 0)*100 << "\n";
	}
	
	
	
	return 0;
}
