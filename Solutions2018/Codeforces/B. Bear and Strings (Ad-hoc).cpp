#include <bits/stdc++.h>

using namespace std;

string b = "bear";

int main(){
	string s;
	cin >> s;
	
	int idx = 0, ans = 0;
	for (int i = 0; i < s.size(); i++)
	{
		idx = 0;
		for (int j = i; j < s.size(); j++)
		{
			if(s[j] == b[idx]) idx++;
			else{
				idx = s[j] == 'b';
			}
			if(idx == 4){
				ans += (int)s.size() - j;
				break;
			}
		}
		
	}
	cout << ans << endl;
	
	return 0;
}
