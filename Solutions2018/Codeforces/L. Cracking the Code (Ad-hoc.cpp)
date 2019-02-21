#include <bits/stdc++.h>

using namespace std;

int main(){
	string s, tmp;
	cin >> s;
	
	tmp += s[0];
	tmp += s[2];
	tmp += s[4];
	tmp += s[3];
	tmp += s[1];
	
	int n = 0;
	
	for (int i = 0; i < 5; i++)
	{
		n *= 10;
		n += tmp[i]-'0';
	}
	
	int ans = n;
	for (int i = 1; i < 5; i++)
	{
		ans = ((long long)ans * n)%100000;
	}
	
	string saida = to_string(ans);
	while(saida.size() < 5) saida = "0" + saida;
	cout << saida << "\n";
	
	
	
	return 0;
}
