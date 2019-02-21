#include <bits/stdc++.h>

using namespace std;
#define MAXN 2000010

int p[MAXN];
string s, text, pattern;
vector<int> saida;

void solve(){
	
	p[0] = 0;
	int idx;
	
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while (s[idx] != s[i] && idx != 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
		
		if(p[i] == (int)pattern.size())
			saida.push_back(i - (int)pattern.size()*2 + 1);
	}
	
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc;
	cin >> tc;
	
	bool fst = true;
	while (tc--)
	{
		if(!fst) cout << "\n";
		fst = false;
		
		cin >> text >> pattern;
		s = pattern + "$" + text;
		saida.clear();
		solve();
		if((int)saida.size() == 0) cout << "Not Found\n";
		else{
			cout << (int)saida.size() << "\n";
			for (int i = 0; i < (int)saida.size(); i++)
			{
				if(i) cout << " ";
				cout << saida[i];
			}
			cout << "\n";
		}
	}
	
	
	
	return 0;
}



//USANDO A FUNCAO DE MATCH
#include <bits/stdc++.h>

using namespace std;
#define MAXN 2000010

int p[MAXN];
string s, text, pattern;
vector<int> saida;

void build(){
	p[0] = 0;
	int idx;
	for (int i = 1; i < (int)pattern.size(); i++)
	{
		idx = p[i-1];
		while (pattern[idx] != pattern[i] && idx != 0)
			idx = p[idx-1];
		
		if(pattern[idx] == pattern[i]) 
			idx++;
		
		p[i] = idx;
	}
}

void solve(){
	build();
	int j = 0;
	for (int i = 0; i < (int)text.size(); i++)
	{
		while (text[i] != pattern[j] && j != 0)
			j = p[j-1];
		
		if(text[i] == pattern[j])
			j++;
		
		
		if(j == (int)pattern.size()){
			saida.push_back(i - (int)pattern.size() + 2);
			j = p[j-1];
		}
		
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc, sz;
	cin >> tc;
	
	bool fst = true;
	while (tc--)
	{
		if(!fst) cout << "\n";
		fst = false;
		
		cin >> text >> pattern;
		
		saida.clear();
		solve();
		sz = (int)saida.size();
		
		if(!sz) cout << "Not Found\n";
		else{
			cout << sz << "\n";
			for (int i = 0; i < sz; i++)
			{
				if(i) cout << " ";
				cout << saida[i];
			}
			cout << "\n";
		}
	}
	
	
	
	return 0;
}


