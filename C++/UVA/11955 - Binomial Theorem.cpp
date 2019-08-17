#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 51
char memo[MAXN][MAXN];
ll dp[MAXN][MAXN];
int n;
ll comb(int a, int b){
	if(a == 0) return b == 0;
	if(memo[a][b]) return dp[a][b];
	memo[a][b] = 1;
	
	return dp[a][b] = comb(a-1, b) + comb(a-1, b-1);
}

int main(){
	int tc;
	cin >> tc;
	string s, s1, s2;
	int pot, caso = 1;
	while (tc--)
	{
		cin >> s;
		for (int i = 0; i < s.size(); i++)
			if(s[i] == '+' || s[i] == '(' || s[i] == ')' || s[i] == '^') s[i] = ' ';
		stringstream ss;
		ss << s;
		ss >> s1;
		ss >> s2;
		ss >> pot;
		n = pot;
		int p1 = pot, p2 = 0;
		
		cout << "Case " << caso++ << ": ";
		while (p2 <= pot)
		{
			if(p1 < pot) cout << "+";
			if(p1 > 0 && p2 > 0){
				cout << comb(n, p1) << "*";
				
				cout << s1;
				if(p1 > 1) cout << "^" << p1;
				
				cout << "*";
				
				cout << s2;
				if(p2 > 1) cout << "^" << p2;
				
			}else if(p1 > 0){
				
				cout << s1;
				if(p1 > 1) cout << "^" << p1;
				
			}else if(p2 > 0){
				
				cout << s2;
				if(p2 > 1) cout << "^" << p2;
				
			}
			
			p1--;
			p2++;
		}
		
		cout << "\n";
	}
	
	
	
	return 0;
}
