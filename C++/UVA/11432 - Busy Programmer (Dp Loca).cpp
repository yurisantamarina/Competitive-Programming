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

int d, mx;
ll dp[68][35][2];
char memo[68][35][2];

ll solve(int dia, int qtdM, int turn){
	if(dia>=2*d) return turn==0 && dia;//&& dia é caso d seja 0
	int qtdG = dia-qtdM;
	if(qtdM==d || qtdG==d) return turn!=0;//se ja acabou algum, só tem uma possibilidade, colocar o outro em tudo, desde q ele nao seja igual a 0, que é o fst
	if(memo[dia][qtdM][turn]) return dp[dia][qtdM][turn];
	memo[dia][qtdM][turn] = 1;
	
	ll ans = 0;
	if(turn==0){
		for (ll i = 1; i <= mx; i++)
		{
			if(qtdM+i > d) break;
			if(dia+i > 2*d) break;
			ans += solve(dia+i, qtdM+i, turn^1);
		}
	}else{
		for (ll i = 1; i <= mx; i++)
		{
			if(qtdG+i > d) break;
			if(dia+i > 2*d) break;
			ans += solve(dia+i, qtdM, turn^1);
		}
	}
	
	
	return dp[dia][qtdM][turn] = ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int caso=1;
	while (cin >> d >> mx)
	{
		if(d==-1 && mx==-1) break;
		memset(memo, 0, sizeof memo);
		cout << "Case " << caso++ << ": " << solve(0, 0, 0)*2 << "\n";
	}
	
	
	return 0;
}
