#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101
int z[MAXN];
string s;

int Z(){
	z[0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	for (int i = 1; i < n; i++)
	{
		z[i] = 0;
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		while(z[i] + i < n && s[z[i]] == s[z[i] + i]) z[i]++;
		if(i+z[i]-1 >= r){
			l = i;
			r = i+z[i]-1;
		}
		if(z[i] == n-i){
			if(n % (n - z[i]) == 0) return n / (n - z[i]);
			return 1;
		}
	}
	return 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while (cin >> s, s!=".")
		cout << Z() << "\n";
	
	
	
	return 0;
}
