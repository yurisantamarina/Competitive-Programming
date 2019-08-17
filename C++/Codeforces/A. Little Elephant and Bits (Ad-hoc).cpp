#include <bits/stdc++.h>

using namespace std;

int main(){
	string s;
	cin >> s;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if(s[i] == '0'){
			cout << s.substr(0, i) << s.substr(i+1) << "\n";
			return 0;
		}
	}
	
	cout << s.substr(1) << "\n";
	
	return 0;
}
