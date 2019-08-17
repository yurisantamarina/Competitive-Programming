#include <bits/stdc++.h>

using namespace std;
string s;
int z[300];

int Z(){
	z[0] = 0;
	int l = 0, r = 0, sz = (int)s.size();
	
	for (int i = 1; i < sz; i++)
	{
		z[i] = 0;
		if(i <= r) z[i] = min(r-i+1, z[i-l]);
		
		while(i+z[i] < sz && s[z[i]] == s[i+z[i]])
			z[i]++;
		
		if(i+z[i] == sz){
			//~ ja achei um sufixo que é prefixo, e como é o primeiro q achei, ele ja é o maior
			//~ AAE$CAA
			//~ 0000021
			//~ o primeiro que devo pegar é o sufixo AA, pois é o maior
			return z[i];
		}
		
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
	}
	
	return 0;
}

int main(){
	int tc, k, n, ans;
	string at, lst;
	cin >> tc;
	while (tc--)
	{
		cin >> k >> n;
		ans = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> at;
			if(i > 0){
				s = at + "$" + lst;
				ans -= Z();
			}
			ans += k;
			lst = at;
		}
		cout << ans << "\n";
	}
	
	
	
	return 0;
}
