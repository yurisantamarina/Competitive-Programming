#include <bits/stdc++.h>

using namespace std;
#define lim 65

long double dp[2][502][502][101];
char memo[2][502][502][101];

int L[]={-1,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5};
int R[]={-1,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1};

long double solve(int turn, int ptA, int ptB, int qtd){
	if(qtd == 0) return 0.0;
	if(ptA == 0) return 1.0;
	if(ptB == 0) return 0.0;
	if(memo[turn][ptA][ptB][qtd]) return dp[turn][ptA][ptB][qtd];
	memo[turn][ptA][ptB][qtd] = 1;
	
	long double ans = 0.0;
	
	int l, r;
	long double x;
	if(turn == 0){
		if(ptA > 20){
			for (int i = 1; i <= 20; i++){
				x = solve(turn ^ 1, ptA - i, ptB, qtd) / 20.0;
				ans += x;
			}
		}else{
			for (int i = 1; i <= 20; i++){
				x = solve(turn ^ 1, ptA - i >= 0 ? ptA - i : ptA, ptB, ptA - i >= 0 ? qtd : qtd-1) / 20.0;
				//~ cout << "x = " << x << endl;
				ans += x;
			}
		}
	}else{
		long double aux = 0.0;
		ans = 1000000000;
		if(ptB > 20){
			for (int i = 1; i <= 20; i++)
			{
				l = L[i];
				r = R[i];
				aux = 0;
				aux += solve(turn ^ 1, ptA, ptB - i, qtd) / 3.0;
				aux += solve(turn ^ 1, ptA, ptB - l, qtd) / 3.0;
				aux += solve(turn ^ 1, ptA, ptB - r, qtd) / 3.0;
				
				ans = min(ans, aux);
			}
		}else{
			for (int i = 1; i <= 20; i++)
			{
				l = L[i];
				r = R[i];
				aux = 0;
				aux += solve(turn ^ 1, ptA, ptB - i >= 0 ? ptB - i : ptB, ptB - i >= 0 ? qtd : qtd - 1) / 3.0;
				aux += solve(turn ^ 1, ptA, ptB - l >= 0 ? ptB - l : ptB, ptB - l >= 0 ? qtd : qtd - 1) / 3.0;
				aux += solve(turn ^ 1, ptA, ptB - r >= 0 ? ptB - r : ptB, ptB - r >= 0 ? qtd : qtd - 1) / 3.0;
				
				ans = min(ans, aux);
			}
			
		}
	}
	
	return dp[turn][ptA][ptB][qtd] = ans;
}

int main(){
	int n;
	while (cin >> n, n)
	{
		cout << fixed << setprecision(8) << solve(0, n, n, lim) << " " << 1.0 - solve(1, n, n, lim) << endl;
	}
	
	
	return 0;
}
