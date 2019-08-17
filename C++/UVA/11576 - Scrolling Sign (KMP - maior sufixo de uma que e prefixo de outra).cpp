#include <bits/stdc++.h>

using namespace std;

string s;
int p[101010];
int k, n;

int kmp(){
	p[0] = 0;
	int idx;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		if(s[idx] == s[i])
			idx++;
		p[i] = idx;
	}
	return p[(int)s.size()-1];
}

int main(){
	int tc, ans;
	cin >> tc;
	string at, lst;
	while (tc--)
	{
		cin >> k >> n;
		ans = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> at;
			if(i){
				s = at + "$" + lst;
				ans -= kmp();
			}
			ans += k;
			lst = at;
		}
		
		cout << ans << "\n";
	}
	
	
	return 0;
}
