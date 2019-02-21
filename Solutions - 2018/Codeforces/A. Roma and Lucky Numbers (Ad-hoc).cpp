#include <bits/stdc++.h>

using namespace std;
int k;

bool ok(int x){
	int cnt = 0;
	while (x)
	{
		cnt += (x%10 == 4 || x%10 == 7);
		x /= 10;
	}
	return cnt <= k;
}

int main(){
	int n, ans = 0, x;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		ans += ok(x);
	}
	cout << ans << endl;
	
	return 0;
}
