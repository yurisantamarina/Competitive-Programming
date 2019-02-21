#include <bits/stdc++.h>

using namespace std;

int n, m, k;
string grid[2010];

int solve(string s){
	stringstream ss;
	//~ cout << s << endl;
	for (int i = 0; i < s.size(); i++)
	{
		if(s[i] == '*') s[i] = ' ';
	}
	
	ss.clear();
	ss << s;
	int ans = 0;
	while (ss >> s)
	{
		if((int)s.size() < k) continue;
		ans += (int)s.size()-k+1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int ans = 0;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> grid[i];
		ans += solve(grid[i]);
	}
	string s;
	for (int i = 0; i < m; i++)
	{
		s = "";
		for (int j = 0; j < n; j++)
		{
			s += grid[j][i];
		}
		ans += solve(s);
	}
	
	if(k == 1) ans /= 2;
	cout << ans << "\n";
	return 0;
}
	
