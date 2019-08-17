#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define MAXN 1000010

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, x;
	cin >> n;
	int lst = -1e9-1;
	ll ans = 0LL;
	ll at = 0LL;
	
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		if(x != lst){
			ans += (at * (at-1))/2 + at;
			at = 1;
		}else at++;
		lst = x;
	}
	ans += (at * (at-1))/2 + at;
	cout << ans << "\n";
	
	
	return 0;
}
