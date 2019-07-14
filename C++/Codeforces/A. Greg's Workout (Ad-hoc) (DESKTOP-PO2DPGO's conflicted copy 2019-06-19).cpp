#include <bits/stdc++.h>

using namespace std;

int v[3];
int main(){
	int n, mx, x;
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		v[i%3]+=x;
	}
	
	mx = 0;
	for (int i = 1; i < 3; i++)
	{
		if(v[i] > v[mx]) mx = i;
	}
	if(mx==0) cout << "chest\n";
	else if(mx == 1) cout << "biceps\n";
	else cout << "back\n";
	
	return 0;
}
