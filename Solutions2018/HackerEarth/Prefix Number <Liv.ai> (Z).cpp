#include <bits/stdc++.h>

using namespace std;

//só é uma resposta valida se o prefixo comecando em i é pelo menos o tamanho do prefixo q ficou pra tras
#define MAXN 101010
int z[MAXN];
string s;
void Z(){
	int l = 0, r = 0, n = (int)s.size();
	z[0] = 0;
	for (int i = 1; i < n; i++)
	{
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		while(z[i] + i < n && s[z[i]] == s[z[i] + i]) z[i]++;
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
	}
}

int main(){
	cin >> s;
	Z();
	
	int ans = 0;
	int n = (int)s.size();
	for (int i = 1; i < n; i++)
	{
		if(s[i] == '0') continue;
		if(z[i] >= i) ans++;
	}
	cout << ans << "\n";
	
	return 0;
}
