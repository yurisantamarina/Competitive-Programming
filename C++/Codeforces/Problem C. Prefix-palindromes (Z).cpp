#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101

string s, tmp;
int z[MAXN];

int Z(){
	z[0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	
	for (int i = 1; i < n; i++)
	{
		if(i <= r)
			z[i] = min(z[i-l], r-i+1);
		
		while(z[i] + i < n && s[z[i] + i] == s[z[i]])
			z[i]++;
		
		if(z[i] == n-i)
			return z[i];
		
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
	}
}

int main(){
	cin >> s;
	tmp = s;
	reverse(tmp.begin(), tmp.end());
	
	s = s + "$" + tmp;
	
	cout << Z() << "\n";
	
	
	return 0;
}
