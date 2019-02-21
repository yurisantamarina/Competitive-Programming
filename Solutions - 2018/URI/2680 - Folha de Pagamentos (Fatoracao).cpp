#include <bits/stdc++.h>

using namespace std;

int solve(int n){
	int ans = 1, at, sum;
	for (int i = 2; n > 1 && i <= 10000; i++)
	{
		at = 1;
		sum = 1;
		while(n % i == 0){
			n /= i;
			at *= i;
			sum += at;
		}
		ans *= sum;
	}
	if(n > 1) ans *= (1 + n);
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tc, n;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		cout << solve(n) << "\n";
	}
	
	
	return 0;
}
