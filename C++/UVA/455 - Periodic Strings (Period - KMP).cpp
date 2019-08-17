#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000010
int p[MAXN];
string s;

int kmp(){
	int idx;
	p[0] = 0;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
		p[i] = idx;
	}
	int n = (int)s.size();
	if(n % (n - p[n-1]) == 0)
		return (n - p[n-1]);
	
	return n;
}

int main(){
	int tc;
	cin >> tc;
	bool fst = true;
	while (tc--)
	{
		if(!fst) cout << "\n";
		fst = false;
		cin >> s;
		cout << kmp() << "\n";
	}
	
	
	
	
	
	return 0;
}
