#include <bits/stdc++.h>

using namespace std;
#define pb push_back

int main(){
	int n, v[1010], mn = 1e9;
	set<int> s;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		s.insert(v[i]);
		mn = min(mn, v[i]);
	}
	
	vector<int> v2;
	v2.pb(mn);
	for (int i = 0; i < n; i++)
	{
		v2.pb(v[i]);
		v2.pb(mn);
	}
	
	int g;
	for (int i = 0; i < v2.size(); i++)
	{
		g = 0;
		for (int j = i; j < v2.size(); j++)
		{
			g = __gcd(g, v2[j]);
			if(!s.count(g)){
				cout << "-1\n";
				return 0;
			}
		}
		
	}
	
	cout << v2.size() << "\n";
	for (int i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << " ";
	}
	cout << "\n";
	return 0;
}
