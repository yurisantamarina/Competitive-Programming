#include <bits/stdc++.h>

using namespace std;

int f[300];

int main(){
	int n;
	string s;
	cin >> n;
	cin >> s;
	
	for (int i = 0; i < n; i++)
	{
		f[s[i]]++;
	}
	int ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		if(s[i] == 'F') continue;
		if(s[i]=='A'){
			if(f['I'] > 0) continue;
			ans++;
		}
		if(s[i]=='I'){
			if(f['I'] > 1) continue;
			ans++;
		}
	}
	cout << ans << endl;
	
}
