//~ http://codeforces.com/gym/101522/problem/J

#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
ll INF = 1000000000000000000LL;
string saida = "";
ll dp[202][202][202][4];
ll K;

ll solve(int B, int R, int S, int lst){
	if(B < 0 || R < 0 || S < 0) return 0;
	if(B == 0 && R == 0 && S == 0) return dp[B][R][S][lst] = 1;
	if(dp[B][R][S][lst]!=-1) return dp[B][R][S][lst];
	
	ll ans = 0LL;
	if(lst != 0){
		ans += solve(B-1, R, S, 0);
		ans = min(ans, INF);
	}
	
	if(lst != 1){
		ans += solve(B, R-1, S, 1);
		ans = min(ans, INF);
	}
	
	if(lst != 2){
		ans += solve(B, R, S-1, 2);
		ans = min(ans, INF);
	}
	
	return dp[B][R][S][lst] = ans;
}

void path(int B, int R, int S, int lst){
	if(B < 0 || R < 0 || S < 0) return;
	if(B == 0 && R == 0 && S == 0) return;
	
	ll ans = 0LL;
	if(lst != 0){
		if(solve(B-1, R, S, 0) >= K){
			saida += 'B';
			path(B-1, R, S, 0);
			return;
		}
		K -= solve(B-1, R, S, 0);
	}
	
	if(lst != 1){
		if(solve(B, R-1, S, 1) >= K){
			saida += 'R';
			path(B, R-1, S, 1);
			return;
		}
		K -= solve(B, R-1, S, 1);
	}
	
	if(lst != 2){
		if(solve(B, R, S-1, 2) >= K){
			saida += 'S';
			path(B, R, S-1, 2);
			return;
		}
	}
	
}

int main(){
	int B, R, S;
	cin >> B >> R >> S >> K;
	
	memset(dp, -1, sizeof dp);
	solve(B, R, S, 3);
	path(B, R, S, 3);
	
	if(saida.size() == B+R+S) cout << saida << "\n";
	else cout << "None\n";
	
	return 0;
}
