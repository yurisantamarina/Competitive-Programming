#include <bits/stdc++.h>

using namespace std;
#define MAXN 3010101
int z[MAXN];
string a, b, s;

int Z(){
	z[0] = 0;
	int l = 0, r = 0, n = (int)s.size(), ans = 0;
	
	for (int i = 1; i < n; i++)
	{
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		while(z[i] + i < n && s[z[i]] == s[z[i] + i]) z[i]++;
		if(z[i] + i - 1 >= r){
			l = i;
			r = z[i] + i - 1;
		}
		if(z[i] > z[ans] && i >= (n-1)/3) ans = i;
	}
	
	return ans - (n-1)/3 - 1;
}

int main(){
	int n;
	cin >> n;
	cin >> a >> b;
	s = a + "$" + b + b;
	cout << Z() << "\n";
	
	return 0;
}
