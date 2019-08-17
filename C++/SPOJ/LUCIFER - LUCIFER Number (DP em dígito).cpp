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
#define MAXN 200

int dp[9][2][85][85];

int auxiliar, auxiliar2;
string s;

bool prime(int n){
	if(n<=1) return false;
	if(n==2) return true;
	if(n%2==0) return false;
	for (int i = 2; i < n; i++)
	{
		if(n%i==0) return false;
	}
	return true;
}

int solve(int pos, int bate, int sumP, int sumI){
	if(pos==s.size()){
		//~ printf("sumP = %d  sumI = %d  sumP-sumI = %d\n", sumP, sumI, sumP - sumI);
		return prime(sumP-sumI) ? 1 : 0;
	}
	if(dp[pos][bate][sumP][sumI]!=-1) return dp[pos][bate][sumP][sumI];
	
	int ans = 0;
	if(bate){
		
		for (int i = 0; i <= s[pos]-'0'; i++)
		{
			if(i==s[pos]-'0') ans += solve(pos+1, true, (s.size()-pos)%2==0 ? sumP + i : sumP, (s.size()-pos)%2!=0 ? sumI + i : sumI);
			else ans += solve(pos+1, false, (s.size()-pos)%2==0 ? sumP + i : sumP, (s.size()-pos)%2!=0 ? sumI + i : sumI);
		}
		
		
	}else{
		for (int i = 0; i < 10; i++)
		{
			ans += solve(pos+1, false, (s.size()-pos)%2==0 ? sumP + i : sumP, (s.size()-pos)%2!=0 ? sumI + i : sumI);
		}
		
	}
	
	return dp[pos][bate][sumP][sumI] = ans;
}

int main () {
	//~ for (int i = 173; i <= 197; i++)
	//~ {
		//~ cout << i << endl;
	//~ }
	
	int t;
	cin >> t;
	while (t--)
	{
		int l, r;
		cin >> l >> r;
		
		int ansL, ansR;
		if(l==0) ansL = 0;
		else{
			l--;
			s = to_string(l);
			
			memset(dp, -1, sizeof dp);
			ansL = solve(0, true, 0, 0);
		}
		
		
		s = to_string(r);
		memset(dp, -1, sizeof dp);
		ansR = solve(0, true, 0, 0);
		cout << ansR - ansL << endl;	
	}
	
	
	
	
	
	
	
	
	
	return 0;
}
