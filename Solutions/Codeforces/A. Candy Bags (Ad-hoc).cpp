#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	int mat[110][110];
	int at = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat[(j+i)%n][i] = at + j;
		}
		at += n;
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	
	
	
	return 0;
}
