#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;

string s;
ll dp[19][2][10][10];

ll solve(int pos, int bate, int fst, int ult){
	if(pos==s.size()) return fst==ult;
	if(dp[pos][bate][fst][ult]!=-1) return dp[pos][bate][fst][ult];
	
	ll ans = 0LL;
	if(bate){
		for (int i = 0; i <= s[pos]-'0'; i++)
		{
			if(i==s[pos]-'0') ans += solve(pos+1, true, fst==0 ? i : fst, i);
			else ans += solve(pos+1, false, fst==0 ? i : fst, i);
		}
	}else{
		for (int i = 0; i < 10; i++)
		{
			ans += solve(pos+1, false, fst==0 ? i : fst, i);
		}
	}
	
	return dp[pos][bate][fst][ult] = ans;
}

int main(){
	ll a, b;
	cin >> a >> b;
	a--;
	
	stringstream ss;
	
	ss << a;
	ss >> s;
	memset(dp, -1, sizeof dp);
	ll ansL = solve(0, true, 0, 0);
	
	ss.clear();
	ss << b;
	ss >> s;
	memset(dp, -1, sizeof dp);
	ll ansR = solve(0, true, 0, 0);
	
	cout << ansR - ansL << "\n";
	
}
