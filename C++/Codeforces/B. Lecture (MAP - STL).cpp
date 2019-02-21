#include <bits/stdc++.h>

using namespace std;

int main(){
	int n, m, idx;
	map<string, int> mapa;
	string s;
	string a[3010], b[3010];
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a[i] >> b[i];
		mapa[a[i]] = i;
		mapa[b[i]] = i;
	}
	
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		idx = mapa[s];
		if(a[idx].size() <= b[idx].size()) cout << a[idx] << " ";
		else cout << b[idx] << " ";
	}
	cout << "\n";
	
	
	return 0;
}
