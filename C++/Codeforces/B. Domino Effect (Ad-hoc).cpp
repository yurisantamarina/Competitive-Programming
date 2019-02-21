#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	string s;
	
	
	cin >> n;
	int r[n];
	int l[n];
	cin >> s;
	
	int at = 0;
	for (int i = 0; i < n; i++)
	{
		if(s[i] == 'R'){
			at = 1;
		}
		if(s[i] == 'L'){
			at = 0;
		}
		
		r[i] = at;
		if(at) at++;
		//~ cout << r[i] << " ";
	}
	//~ cout << endl;
	
	at = 0;
	int ans = 0;
	for (int i = n-1; i >= 0; i--)
	{
		if(s[i] == 'L'){
			at = 1;
		}
		if(s[i] == 'R'){
			at = 0;
		}
		
		l[i] = at;
		if(l[i] == r[i]) ans++;
		if(at) at++;
	}
	//~ for (int i = 0; i < n; i++)
	//~ {
		//~ cout << l[i] << " ";
	//~ }
	//~ cout << endl;
	
	cout << ans << "\n";
	
	return 0;
}
