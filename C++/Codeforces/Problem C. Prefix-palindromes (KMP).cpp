//~ http://codeforces.com/group/eqgxxTNwgd/contest/101245/attachments

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
string s, tmp;
int p[MAXN];

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
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	tmp = s;
	reverse(tmp.begin(), tmp.end());
	s = s + "$" + tmp;
	cout << kmp() << "\n";
	
	
	return 0;
}
