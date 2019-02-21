#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 101010

int c[120][120];
int turn[120];
int main(){
	fast;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> c[i][j];
			if(i == j) continue;
			if(c[i][j] == 1) turn[i]++;
			else if(c[i][j] == 2) turn[j]++;
			else if(c[i][j] == 3){
				turn[i]++;
				turn[j]++;
			}
		}
	}
	
	vector<int> ans;
	for (int i = 0; i < n; i++)
	{
		if(turn[i] == 0) ans.pb(i+1);
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
	
	
	
	
	return 0;
}
