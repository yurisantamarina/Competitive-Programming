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

int tam, hDesejada, qtdPicosDesejada;
int dp[45][45][45][2];

int solve(int i, int hAtual, int qtdPicosAtual, int subiu){
	if(i==2*tam) return hAtual == 0 && qtdPicosAtual == qtdPicosDesejada;
	if(hAtual < 0 || qtdPicosAtual > qtdPicosDesejada) return 0;
	if(dp[i][hAtual][qtdPicosAtual][subiu] != -1) return dp[i][hAtual][qtdPicosAtual][subiu];
	
	int ans=0;
	if(hAtual==0){
		ans = solve(i+1, 1, qtdPicosAtual, true);
	}else if(hAtual==hDesejada){
		if(subiu){
			ans += solve(i+1, hAtual+1, qtdPicosAtual, true);
			ans += solve(i+1, hAtual-1, qtdPicosAtual+1, false);
		}else{
			ans += solve(i+1, hAtual+1, qtdPicosAtual, true);
			ans += solve(i+1, hAtual-1, qtdPicosAtual, false);
		}
	}else{
		ans += solve(i+1, hAtual+1, qtdPicosAtual, true);
		ans += solve(i+1, hAtual-1, qtdPicosAtual, false);
	}
	
	return dp[i][hAtual][qtdPicosAtual][subiu] = ans;
}

int main() {
	//~ int r;
	while (cin >> tam >> qtdPicosDesejada >> hDesejada)
	{
		memset(dp, -1, sizeof dp);
		
		cout << solve(0, 0, 0, 0) << endl;
	}
	

    

    return 0;
}
