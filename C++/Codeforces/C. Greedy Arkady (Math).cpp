#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
ll n, k, M, D, ans = 0;
long double x;

int main(){
	cin >> n >> k >> M >> D;
	for (ll d = 1; d <= D; d++)
	{
		//x <= n / ((d-1) * k + 1)
		x = n / ((long double)(d-1) * k + 1);
		//~ printf("x = %lld / ((%lld) * %lld + 1)\n", n, d-1, k);
		//~ printf("d = %lld  x = %lld\n", d, x);
		//~ if(x < 0) continue;
		if(x > M) x = M;
		//~ if(x * d * k + x <= n) continue;
		ans = max(ans, (ll)x * d);
	}
	cout << fixed << setprecision(0) << ans << "\n";
	return 0;
}
