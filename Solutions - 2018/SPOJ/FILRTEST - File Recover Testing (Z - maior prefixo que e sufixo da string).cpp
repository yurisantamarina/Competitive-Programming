#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101

string s;
int L;
int z[MAXN];

int Z(){
	z[0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	
	for (int i = 1; i < n; i++)
	{
		z[i] = 0;
		if(i <= r)
			z[i] = min(z[i-l], r - i + 1);
		
		while(i + z[i] < n && s[z[i]] == s[i+z[i]])
			z[i]++;
		
		if(i+z[i]-1 >= r){
			l = i;
			r = i+z[i]-1;
		}
		
		if(z[i] == n - i)
			return z[i];
	}
	
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while (cin >> L >> s)
	{
		if(L == -1 && s == "*") break;
		if((int)s.size() > L)
			cout << "0\n";
		else
			cout << ((L-(int)s.size())/((int)s.size() - Z()))+1 << "\n";
	}	
	
	return 0;
}
