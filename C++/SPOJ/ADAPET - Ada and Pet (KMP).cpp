#include <bits/stdc++.h>

using namespace std;
#define MAXN 500010
typedef long long int ll;
string s;
int p[MAXN];
ll k;

int lps(){
	p[0] = 0;
	
	int idx;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while (s[idx] != s[i] && idx != 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
	}
	
	return p[(int)s.size()-1];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> s >> k;
		cout << (ll)s.size() + ((ll)s.size() - lps()) * (k-1) << "\n";
	}
	
	
	return 0;
}
