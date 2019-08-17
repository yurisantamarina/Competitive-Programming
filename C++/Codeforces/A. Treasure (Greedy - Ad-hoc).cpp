#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s, at="";
	int abreT=0, lst, qtd=0, fecha=0, falta, fechaT = 0;
	
	cin >> s;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if(s[i]=='('){
			abreT++;
		}else if(s[i]=='#'){
			lst = i;
			qtd++;
		}else{
			fecha++;
		}
	}
	
	vector<int> ans;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if(s[i]==')'){
			at += s[i];
		}else if(s[i]=='#'){
			if(i == lst){
				falta = abreT - fecha;
				if(falta <= 0){
					cout << "-1\n";
					return 0;
				}
				ans.push_back(falta);
				while (falta--){
					at += ')';
					fecha++;
				}
				
			}else{
				at += ')';
				fecha++;
				ans.push_back(1);
			}
		}else{
			at += s[i];
		}
		
	}
	int abre = 0;
	fecha = 0;
	for (int i = 0; i < (int)at.size(); i++)
	{
		if(at[i] == '(') abre++;
		else{
			fecha++;
			if(fecha > abre){
				cout << "-1\n";
				return 0;
			}
		}
	}
	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i] << "\n";
	}
	
	
	
	
	return 0;
}
