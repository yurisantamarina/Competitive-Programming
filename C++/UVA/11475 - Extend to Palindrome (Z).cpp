#include <bits/stdc++.h>

using namespace std;

int z[201010];
string s, tmp;

int Z(){
	z[0] = 0;
	int sz = (int)s.size(), l = 0, r = 0;
	
	//~ cout << s << "\n0 ";
	for (int i = 1; i < sz; i++)
	{
		if(i > r){
			l = i;
			r = i;
			while(r < sz && s[r] == s[r-l])
				r++;
			
			r--;
			z[i] = r-l+1;
		}else{
			int nw = i - l;
			if(z[nw] + i - 1 < r)
				z[i] = z[nw];
			else{
				l = i;
				while(r < sz && s[r] == s[r-l])
					r++;
				
				r--;
				z[i] = r-l+1;
			}
		}
		
		//~ cout << z[i] << " ";
	}
	//~ cout << endl;
	
	int ans = 0;
	for (int i = sz-1, cnt = 0; i >= 0; i--, cnt++)
	{
		if(z[i] == cnt+1)
			ans = z[i];
	}
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string cp;
	while (cin >> s)
	{
		tmp = s;
		cp = s;
		reverse(tmp.begin(), tmp.end());
		s = tmp + "$" + s;
		int ans = Z();
		//~ cout << ans << endl;
		
		cout << cp;
		for (int i = (int)cp.size()-ans-1; i >= 0; i--)
			cout << cp[i];
		
		cout << "\n";
	}
	
	
	return 0;
}
