#include <bits/stdc++.h>

using namespace std;
#define pb push_back

vector<int> peso;
int m;
char memo[1010][11][50];
bool dp[1010][11][50];

bool solve(int qtd, int lst, int dif){
	if(qtd == 0) return true;
	if(memo[qtd][lst][dif + 20]) return dp[qtd][lst][dif + 20];
	memo[qtd][lst][dif + 20] = 1;
	
	bool ans = false;
	int sinal = qtd%2 ? 1 : -1;
	if(qtd == m){
		
		for (int i = 0; i < (int)peso.size(); i++)
		{
			ans |= solve(qtd-1, peso[i], dif + sinal * peso[i]);
		}
		
	}else{
		
		for (int i = 0; i < (int)peso.size(); i++)
		{
			if(peso[i] == lst) continue;
			if(peso[i] <= abs(dif)) continue;
			ans |= solve(qtd-1, peso[i], dif + sinal * peso[i]);
		}
		
		
	}
	
	return dp[qtd][lst][dif + 20] = ans;
}

void path(int qtd, int lst, int dif){
	if(qtd == 0) return;
	
	bool ans = solve(qtd, lst, dif);
	int sinal = qtd%2 ? 1 : -1;
	if(qtd == m){
		
		for (int i = 0; i < (int)peso.size(); i++)
		{
			if(ans == solve(qtd-1, peso[i], dif + sinal * peso[i])){
				cout << peso[i] << " ";
				path(qtd-1, peso[i], dif + sinal * peso[i]);
				return;
			}
		}
		
	}else{
		
		for (int i = 0; i < (int)peso.size(); i++)
		{
			if(peso[i] == lst) continue;
			if(peso[i] <= abs(dif)) continue;
			if(ans == solve(qtd-1, peso[i], dif + sinal * peso[i])){
				cout << peso[i] << " ";
				path(qtd-1, peso[i], dif + sinal * peso[i]);
				return;
			}
		}
		
		
	}
}

int main(){
	string s;
	cin >> s;
	cin >> m;
	
	for (int i = 0; i < (int)s.size(); i++)
	{
		if(s[i] == '1') peso.pb(i+1);
	}
	
	bool ans = solve(m, 0, 0);
	if(ans){
		cout << "YES\n";
		path(m, 0, 0);
		cout << "\n";
	}else{
		cout << "NO\n";
	}
	
	return 0;
}
