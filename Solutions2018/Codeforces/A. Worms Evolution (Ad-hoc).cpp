#include <bits/stdc++.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	int v[n];
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(i == j) continue;
			for (int k = 0; k < n; k++)
			{
				if(j == k) continue;
				if(v[i] == v[j] + v[k]){
					cout << i+1 << " " << j+1 << " " << k+1 << endl;
					return 0;
				}
			}
		}
	}
	cout << "-1\n";
	
	
	return 0;
}
