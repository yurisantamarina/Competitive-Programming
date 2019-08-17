#include <bits/stdc++.h>

using namespace std;
string s, tmp;
int z[2101010];
int Z(){
	z[0] = 0;
	int l = 0, r = 0;
	int sz = (int)s.size();
	int ans = 0;
	
	for (int i = 1; i < sz; i++)
	{
		z[i] = 0;
		if(i <= r)
			z[i] = min(r-i+1, z[i-l]);
		
		while(i + z[i] < sz && s[z[i]] == s[i + z[i]])
			z[i]++;
		
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
		
		if(i > (sz-1)/2) 
			ans = max(ans, z[i]);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	while (n--)
	{
		cin >> s;
		tmp = s;
		reverse(tmp.begin(), tmp.end());
		s = s + "$" + tmp;
		int ans = Z();
		
		for (int i = ans-1; i >= 0; i--)
			cout << s[i];
		cout << "\n";
	}
	
	
	
	return 0;
}
