#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
int n, k;
char grid[120][120];
int cnt[120][120];

int main(){
	int k, n, s, p;
	cin >> k >> n >> s >> p;
	int per = n / s;
	if(n % s) per++;
	int tot = per * k;
	int ans = tot / p;
	if(tot % p) ans++;
	cout << ans << "\n";
	
	return 0;
}
