#include <bits/stdc++.h>

using namespace std;
#define MAXN 3001010

string s;
int p[MAXN];

int kmp(){
	int idx;
	int lst = -1;
	p[0] = 0;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx != 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
		
		p[i] = idx;
		if(p[i]*3 + 1 == (int)s.size()){
			if(lst != -1) return (((int)s.size()-1)/3) / (i - lst);
			lst = i;
		}
	}
	
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while (cin >> s, s!=".")
	{
		s = s + "$" + s + s;
		//~ cout << s << endl;
		cout << kmp() << "\n";
	}
	
	
	return 0;	
}
