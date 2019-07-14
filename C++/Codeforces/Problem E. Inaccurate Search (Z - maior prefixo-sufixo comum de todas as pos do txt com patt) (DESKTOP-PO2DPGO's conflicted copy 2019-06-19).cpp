#include <bits/stdc++.h>

using namespace std;
#define MAXN 2010101

string text, pattern, s, tmp;
vector<int> ans;
int k;
int z[2][MAXN];

void Z(int op){
	z[op][0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	
	for (int i = 1; i < n; i++)
	{
		if(i <= r) z[op][i] = min(z[op][i-l], r-i+1);
		
		while(i + z[op][i] < n && s[z[op][i]] == s[i + z[op][i]])
			z[op][i]++;
		
		if(i + z[op][i] - 1 >= r){
			l = i;
			r = i + z[op][i] - 1;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> text >> pattern >> k;
	
	if((int)text.size() < (int)pattern.size()){
		cout << "0\n";
		return 0;
	}
	
	s = pattern + "$" + text;
	Z(0);
	
	tmp = pattern;
	reverse(tmp.begin(), tmp.end());
	s = tmp + "$";
	
	tmp = text;
	reverse(tmp.begin(), tmp.end());
	s += tmp;
	Z(1);
	
	int l1 = (int)pattern.size() + 1, r1 = l1 + (int)pattern.size() - 1;
	int l2 = (int)s.size() - (int)pattern.size(), r2 = l2 + (int)pattern.size() - 1;
	
	while (r1 < (int)s.size())
	{
		
		if((int)pattern.size() - z[0][l1] - z[1][l2] <= k)
			ans.push_back(l1 - (int)pattern.size());
		
		l1++; r1++;
		l2--; r2--;
	}
	
	cout << (int)ans.size() << "\n";
	
	if((int)ans.size()){
		
		for (int i = 0; i < (int)ans.size(); i++)
		{
			if(i) cout << " ";
			cout << ans[i];
		}
		cout << "\n";
		
	}
	
	return 0;
}
