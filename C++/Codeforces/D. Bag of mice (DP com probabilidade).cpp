#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
#define mp make_pair
#define MOD 1000000007
#define PRINCESA 0
#define DRAGAO 1

double dp[2][MAXN][MAXN];
char memo[2][MAXN][MAXN];

double solve(int at, int w, int b){
	if(w + b <= 1)
		return at == PRINCESA && w == 1 ? 1.0 : 0.0;
	if(memo[at][w][b])
		return dp[at][w][b];
		
	memo[at][w][b] = 1;
	
	double ans = 0LL;
	
	if(at == PRINCESA){
		if(w > 0){//probabilidade da princisa tirar um branco (ganha)
			ans += ((w*1.0) / (w + b));
		}
		if(b > 0){//probabilidade da princesa tirar um preto e passar para o dragao
			ans += ((b*1.0) / (w + b)) * solve(at^1, w, b-1);
		}
	}else{
		//probabilidade do dragao tirar um branco e fazer a princesa perder tem q somar 0 na resposta pois a princesa nao ganha nesse caso, por isso q eu nem somo nada aqui;
		//~ ans += 0.0;
		
		if(b > 0 && w > 0){//probabilidade do dragao tirar um preto e descartar um branco e passar para a princesa
			ans += ((b*1.0) / (w + b)) * ((w*1.0) / (w + b - 1)) * solve(at^1, w-1, b-1);
		}
		if(b > 1){//probabilidade do dragao tirar um preto e descartar um preto e passar para a princesa
			ans += ((b*1.0) / (w + b)) * ((b*1.0 - 1.0) / (w + b - 1)) * solve(at^1, w, b-2);
		}
	}
	
	return dp[at][w][b] = ans;
}

int main(){
	int w, b;
	cin >> w >> b;
	cout << fixed << setprecision(10) << solve(PRINCESA, w, b) << "\n";
	
	
	
	return 0;
}
