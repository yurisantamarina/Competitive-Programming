#include <bits/stdc++.h>

using namespace std;
#define MAXN 501010

int p[MAXN];
string s, tmp, cp;

int kmp(){
	p[0] = 0;
	int idx;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
			
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
	}
	
	return p[(int)s.size()-1];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int ans;
	while (cin >> s)
	{
		tmp = s;
		cp = s;
		reverse(tmp.begin(), tmp.end());
		s = tmp + "$" + s;
		
		ans = kmp();
		cout << cp;
		for (int i = (int)cp.size() - ans - 1; i >= 0; i--)
			cout << cp[i];
		cout << "\n";
	}
	
	
	
	return 0;
}
