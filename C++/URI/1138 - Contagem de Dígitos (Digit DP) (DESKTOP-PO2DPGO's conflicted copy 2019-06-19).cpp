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

string s;
int tam;
int dp0[10][2][10][2];
int dp[10][2][10];
int digitoProcurado;

int solve0(int pos, bool bate, int qtd, bool comecou){
	if(pos == tam) return qtd;
	if(dp0[pos][bate][qtd][comecou]!=-1) return dp0[pos][bate][qtd][comecou];
	
	int ans = 0;
	if(bate){
		for (int i = 0; i < s[pos]-'0'; i++)
		{
			if(i==0){
				ans += solve0(pos+1, false, comecou ? qtd+1 : 0, comecou);
			}else{
				ans += solve0(pos+1, false, qtd, true);
			}
		}
		
		if(s[pos]=='0')
			ans += solve0(pos+1, true, comecou ? qtd+1 : 0, comecou);
		else
			ans += solve0(pos+1, true, qtd, true);
			
	}else{
		for (int i = 0; i < 10; i++)
		{
			if(i==0){
				ans += solve0(pos+1, false, comecou ? qtd+1 : 0, comecou);
			}else{
				ans += solve0(pos+1, false, qtd, true);
			}
		}
	}
	
	return dp0[pos][bate][qtd][comecou] = ans;
}

int solve(int pos, int bate, int qtd){
	if(pos == tam) return qtd;
	if(dp[pos][bate][qtd]!=-1) return dp[pos][bate][qtd];
	
	int ans = 0;
	if(bate){
		for (int i = 0; i <= s[pos]-'0'; i++)
		{
			ans += solve(pos+1, i == s[pos]-'0' ? true : false, i == digitoProcurado ? qtd+1 : qtd);
		}
	}else{
		for (int i = 0; i < 10; i++)
		{
			ans += solve(pos+1, false, i==digitoProcurado ? qtd+1 : qtd);
		}
		
	}
	
	return dp[pos][bate][qtd] = ans;
}

int main () {
	string a, b;
	int ans[10];
	while (cin >> a >> b)
	{
		if(a=="0" && b=="0") break;
		memset(ans, 0, sizeof ans);
		
		int n;
		stringstream ss;
		ss << a;
		ss >> n;
		n--;
		a = to_string(n);
		s = b;
		tam = s.size();
		for (int i = 0; i < 10; i++)
		{
			memset(dp0, -1, sizeof dp0);
			memset(dp, -1, sizeof dp);
			digitoProcurado = i;
			if(i==0) ans[i] = solve0(0, 1, 0, 0);
			else ans[i] = solve(0, 1, 0);
		}
		
		s = a;
		tam = s.size();
		for (int i = 0; i < 10; i++)
		{
			memset(dp0, -1, sizeof dp0);
			memset(dp, -1, sizeof dp);
			digitoProcurado = i;
			if(i==0) ans[i] -= solve0(0, 1, 0, 0);
			else ans[i] -= solve(0, 1, 0);
		}
		
		for (int i = 0; i < 10; i++)
		{
			if(i) cout << " ";
			cout << ans[i];
		}
		cout << endl;
		
		
	}
	
	
	return 0;
}
