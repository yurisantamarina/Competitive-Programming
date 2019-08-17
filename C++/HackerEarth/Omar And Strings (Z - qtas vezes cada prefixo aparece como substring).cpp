#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101

string s, text, rev;
int z[3][MAXN];
int ans[MAXN];

void Z(int op){
	z[op][0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	
	for (int i = 1; i < n; i++)
	{
		if(i <= r)
			z[op][i] = min(z[op][i-l], r-i+1);
			
		while(z[op][i] + i < n && s[z[op][i]] == s[z[op][i]+i])
			z[op][i]++;
		
		if(i + z[op][i] - 1 >= r){
			l = i;
			r = i + z[op][i] - 1;
		}
	}
}

int get(int op){
	int n = (int)s.size();
	for (int i = 0; i < n; i++)
	{
		if(z[op][i] == n-i)
			return z[op][i];
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> text;
	rev = text;
	reverse(text.begin(), text.end());
	
	s = text + "$" + rev;
	Z(0);
	int lp = get(0);
	
	s = rev + "$" + text;
	Z(1);
	int ls = get(1);
	
	s = text.substr(0, lp) + rev.substr(0, ls);
	Z(2);
	
	int n = (int)s.size();

	z[2][0] = n;
	
	for (int i = 0; i < n; i++)
	{
		if(z[2][i] > 0){
			ans[1]++;
			ans[z[2][i] + 1]--;
		}
	}
	
	cout << s << "\n";
	for (int i = 1; i <= n; i++)
	{
		ans[i] += ans[i-1];
		cout << ans[i] << " ";
	}
	cout << "\n";
	
}
