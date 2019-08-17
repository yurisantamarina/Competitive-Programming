#include <bits/stdc++.h>

using namespace std;
#define MAXN 500100
#define LIM 3

using ll = long long int;
int dp[MAXN][28];
char memo[MAXN][28];
int n, k;
string s;

int solve(int pos, int lst){
	if(pos == (int)s.size()) return 0;
	if(memo[pos][lst]) return dp[pos][lst];
	memo[pos][lst] = 1;
	
	int ans = 1e9, cnt = 0;
	
	if(pos > 0){
		for (int i = lst+1; i < k && cnt < LIM; i++)
		{
			if(lst == i) continue;
			cnt++;
			ans = min(ans, (s[pos]-'A' != i) + solve(pos+1, i));
		}
		
		cnt = 0;
		for (int i = lst-1; i >= 0 && cnt < LIM; i--)
		{
			if(lst == i) continue;
			cnt++;
			ans = min(ans, (s[pos]-'A' != i) + solve(pos+1, i));
		}
		
		if(s[pos]-'A' != lst){
			ans = min(ans, solve(pos+1, s[pos]-'A'));
		}
	}else{
		for (int i = 0; i < k; i++)
		{
			ans = min(ans, (s[pos]-'A' != i) + solve(pos+1, i));
		}
	}
	
	return dp[pos][lst] = ans;
}

void path(int pos, int lst){
	if(pos == (int)s.size()) return;
	
	int ans = solve(pos, lst), cnt = 0;
	
	if(pos > 0){
		for (int i = lst+1; i < k && cnt < LIM; i++)
		{
			if(lst == i) continue;
			cnt++;
			if(ans == (s[pos]-'A' != i) + solve(pos+1, i)){
				cout << char(i+'A');
				path(pos+1, i);
				return;
			}
		}
		
		cnt = 0;
		for (int i = lst-1; i >= 0 && cnt < LIM; i--)
		{
			if(lst == i) continue;
			cnt++;
			if(ans == (s[pos]-'A' != i) + solve(pos+1, i)){
				cout << char(i+'A');
				path(pos+1, i);
				return;
			}
		}
		
		if(s[pos]-'A' != lst){
			cout << char(s[pos]);
			path(pos+1, s[pos]-'A');
		}
	}else{
		for (int i = 0; i < k; i++)
		{
			if(ans == (s[pos]-'A' != i) + solve(pos+1, i)){
				cout << char(i+'A');
				path(pos+1, i);
				return;
			}
		}
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	cin >> s;
	cout << solve(0, 0) << "\n"; 
	path(0, 0);
	cout << "\n";
	
	
	return 0;
}
