#include <bits/stdc++.h>

using namespace std;
#define MAXN 501010
string s;
int p[MAXN];

int solve(){
	int ans = 0, idx;
	p[0] = 0;
	
	for (int i = 1; i < (int)s.size()-1; i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
		
		p[i] = idx;
		if(p[i] == ((int)s.size()-1)/3) ans++;
	}
	
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc;
	string a, b;
	cin >> tc;
	while (tc--)
	{
		cin >> a >> b;
		s = a + "$" + b + b;
		
		cout << solve() << "\n";
	}
	
	
	
	return 0;
}
