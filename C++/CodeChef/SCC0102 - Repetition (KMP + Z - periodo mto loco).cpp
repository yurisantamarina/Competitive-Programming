#include <bits/stdc++.h>
 
using namespace std;

//~ Preciso pegar para cada prefixo, qual o período dele e checar se o sufixo que restou é prefixo da string
#define MAXN 1000010
int z[MAXN];
int p[MAXN];
string s;
 
void KMP(){
	p[0] = 0;
	int idx = 0, n = (int)s.size();
	//~ cout << "KMP = 0 ";
	for (int i = 1; i < n; i++)
	{
		while(s[idx] != s[i] && idx > 0) idx = p[idx-1];
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
		//~ cout << idx << " ";
	}
	//~ cout << endl;
}
 
void Z(){
	z[0] = 0;
	int l = 0, r = 0, n = (int)s.size();
	//~ cout << "Z = 0 ";
	for (int i = 1; i < n; i++)
	{
		z[i] = 0;
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		while(i + z[i] < n && s[z[i]] == s[z[i] + i]) z[i]++;
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
		//~ cout << z[i] << " ";
	}
	//~ cout << endl;
}
 
int solve(){
	int n = (int)s.size();
	int ans = n, len;
	for (int i = 0; i < n-1; i++)
	{
		if(i + 1 < n - i - 1) continue;
		if((i + 1) % (i + 1 - p[i]) == 0){
			len = (i + 1) / (i + 1 - p[i]);
			len = (i + 1) / len;
		}else len = i + 1;
		
		if(z[i+1] == n - i - 1)	ans = min(ans, len);
	}
	return ans;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc, n, qtd;
	string aux;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		s = "";
		for (int i = 0; i < n; i++)
		{
			cin >> qtd >> aux;
			while (qtd-- > 0) s += aux;
		}
		//~ cout << s << endl;
		
		KMP();
		Z();
		
		cout << solve() << "\n";
	}
	
	
	return 0;
}
