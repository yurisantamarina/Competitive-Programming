#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
int p[MAXN];
string s;

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
	int n = (int)s.size();
	if(n % (n - p[n-1]) == 0) return n / (n - p[n-1]);
	
	return 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while (cin >> s, s!="*")
		cout << kmp() << "\n";
	
	
	
	
	return 0;
}
