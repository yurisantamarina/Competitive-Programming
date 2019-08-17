#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};

string bin;
ll dp[60][2][60];
int tam;

ll solve(int pos, int bate, int qtd){
	if(pos==tam) return qtd;
	if(dp[pos][bate][qtd]!=-1) return dp[pos][bate][qtd];
	
	ll ans=0LL;
	if(bate){
		for (int i = 0; i <= bin[pos]-'0'; i++)
		{
			if(i==bin[pos]-'0'){
				ans += solve(pos+1, true, i==1 ? qtd+1LL : qtd);
			}else{
				ans += solve(pos+1, false, i==1 ? qtd+1LL : qtd);
			}
		}
		
	}else{
		for (int i = 0; i < 2; i++)
		{
			ans += solve(pos+1, false, i==1 ? qtd+1 : qtd);
		}
		
	}
	return dp[pos][bate][qtd] = ans;
}

int main () {
	ll l, r;
	
	while (cin >> l >> r)
	{
		bitset<60> b;
		l--;
		b = l;
		ll ansL, ansR;
		
		bin = b.to_string();
		tam = bin.size();
		//~ cout << bin << endl;
		memset(dp, -1, sizeof dp);
		ansL = solve(0, true, 0);
		
		b = r;
		bin = b.to_string();
		tam = bin.size();
		//~ cout << bin << endl;
		memset(dp, -1, sizeof dp);
		ansR = solve(0, true, 0);
		cout << ansR - ansL << endl;
	}
	
	return 0;
}
