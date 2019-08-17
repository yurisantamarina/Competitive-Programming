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

int dp[8][8][8][8][4][4][4][4];
char memo[8][8][8][8][4][4][4][4];
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int solve(int q0, int q1, int q2, int q3, int tamLast, int corLast, int tamFirst, int corFirst){
	
	if(q0 < 0 || q1 < 0 || q2 < 0 || q3 < 0) return 0;
	
	if(q0+q1+q2+q3 == 0) return corLast != corFirst && tamLast != tamFirst;
	if(memo[q0][q1][q2][q3][tamLast][corLast][tamFirst][corFirst]) return dp[q0][q1][q2][q3][tamLast][corLast][tamFirst][corFirst];
	memo[q0][q1][q2][q3][tamLast][corLast][tamFirst][corFirst] = 1;
	
	int mn;
	int ans = 0;
	if(tamFirst == 0){//nao comecou
		mn = min(q0, 3);
		for (int i = 1; i <= mn; i++)
		{
			ans += solve(q0-i, q1, q2, q3, i, 0, i, 0);
		}
		mn = min(q1, 3);
		for (int i = 1; i <= mn; i++)
		{
			ans += solve(q0, q1-i, q2, q3, i, 1, i, 1);
		}
		mn = min(q2, 3);
		for (int i = 1; i <= mn; i++)
		{
			ans += solve(q0, q1, q2-i, q3, i, 2, i, 2);
		}
		mn = min(q3, 3);
		for (int i = 1; i <= mn; i++)
		{
			ans += solve(q0, q1, q2, q3-i, i, 3, i, 3);
		}
	}else{
		if(corLast == 0){
			mn = min(q1, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1-i, q2, q3, i, 1, tamFirst, corFirst);
			}
			mn = min(q2, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1, q2-i, q3, i, 2, tamFirst, corFirst);
			}
			mn = min(q3, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1, q2, q3-i, i, 3, tamFirst, corFirst);
			}
		}else if(corLast == 1){
			mn = min(q0, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0-i, q1, q2, q3, i, 0, tamFirst, corFirst);
			}
			mn = min(q2, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1, q2-i, q3, i, 2, tamFirst, corFirst);
			}
			mn = min(q3, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1, q2, q3-i, i, 3, tamFirst, corFirst);
			}
		}else if(corLast == 2){
			mn = min(q0, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0-i, q1, q2, q3, i, 0, tamFirst, corFirst);
			}
			mn = min(q1, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1-i, q2, q3, i, 1, tamFirst, corFirst);
			}
			mn = min(q3, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1, q2, q3-i, i, 3, tamFirst, corFirst);
			}
		}else{
			mn = min(q0, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0-i, q1, q2, q3, i, 0, tamFirst, corFirst);
			}
			mn = min(q1, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1-i, q2, q3, i, 1, tamFirst, corFirst);
			}
			mn = min(q2, 3);
			for (int i = 1; i <= mn; i++)
			{
				if(i==tamLast) continue;
				ans += solve(q0, q1, q2-i, q3, i, 2, tamFirst, corFirst);
			}
		}
	}
	
	return dp[q0][q1][q2][q3][tamLast][corLast][tamFirst][corFirst] = ans;
}

int main () {
	
	int tc;
	
	scanint(tc);
	int dif = 0;
	int v[5];
	int q;
	while (tc--)
	{
		scanint(q);
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
		v[3] = 0;
		dif = 0;
		for (int i = 0; i < q; i++)
		{
			scanint(v[i]);
			dif += (v[i]>0);
		}
		if(dif==1){
			for (int i = 0; i < q; i++)
			{
				if(v[i]>0){
					printf("%d\n", v[i]<=3 ? 1 : 0);
					break;
				}
			}
			
			continue;
		}
		if(dif==0){
			printf("1\n");
			continue;
		}
		
		//~ memset(memo, 0, sizeof memo);
		//NÃO PRECISO ZERAR A DP TODAS AS VEZES
		printf("%d\n", solve(v[0], v[1], v[2], v[3], 0, 0, 0, 0));
	}
	
	
	return 0;
}
