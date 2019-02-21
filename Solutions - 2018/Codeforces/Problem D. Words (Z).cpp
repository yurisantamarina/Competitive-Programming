#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101
string s, k, t;
int z[MAXN];

void Z(){
	z[0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	
	for (int i = 1; i < n; i++)
	{
		if(i <= r)
			z[i] = min(z[i-l], r-i+1);
		
		while(z[i] + i < n && s[z[i]] == s[z[i]+i])
			z[i]++;
		
		if(i+z[i]-1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k >> t;
	
	if((int)k.size() != (int)t.size()){
		cout << "No\n";
		return 0;
	}
	
	int len = 0, l = 0, r = (int)t.size() - 1;
	while(l < (int)k.size() && k[l++] == t[r--])
		len++;
	
	s = t + "$" + k;
	Z();
	int n = (int)s.size();
	int resto;
	
	for (int i = (n-1)/2; i < n; i++)
	{
		if(z[i] == n-i){//achei um prefixo que é sufixo de tamanho z[i]
			resto = ((n-1)/2) - z[i];
			if(len >= resto){
				cout << "Yes\n" << resto << "\n";
				return 0;
			}
		}
	}
	cout << "No\n";
	
	
	
	
	return 0;
}
