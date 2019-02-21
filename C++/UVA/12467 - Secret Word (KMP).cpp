#include <bits/stdc++.h>

using namespace std;
#define MAXN (int)2e6+10
int p[MAXN];
string s, tmp;

//~ s + $ + rev(s);
//~ eu preciso de um prefixo invertido da string que aparece como substring, quando eu inverto e concateno, depois do $ o valor de p[i] representa uma string que termina em i e é prefixo, so que ela ta invertida, entao representa a substring que comeca em i (alterado) e tem tamanho p[i] e é inverso do prefixo;

int kmp(){
	p[0] = 0;
	int idx, mx = 0;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
			
		p[i] = idx;
		if(i > (int)tmp.size())//para nao pegar um prefixo que é sufixo antes do '$'
			mx = max(mx, p[i]);
	}
	
	return mx;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	int ans;
	
	while (n--)
	{
		cin >> s;
		tmp = s;
		reverse(tmp.begin(), tmp.end());
		s = s + "$" + tmp;
		ans = kmp();
		
		for (int i = ans-1; i >= 0; i--)
			cout << s[i];
		cout << "\n";
		
		
	}
	
	
	return 0;
}
