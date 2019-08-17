#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
ll n, k, v[101010];
int main () {
	scanf("%lld %lld", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &v[i]);
	}
	sort(v, v+n);
	ll l=0, r=0;
	ll sum = v[l];
	ll mx = 0, val = 0, need;
	while (r < n)
	{
		need = v[r] * (r-l+1) - sum;
		if(need <= k){
			if(r-l+1 == mx){
				val = min(val, v[r]);
			}else if(r-l+1 > mx){
				mx = r-l+1;
				val = v[r];
			}
			r++;
			if(r < n) sum += v[r];
		}else{
			sum -= v[l];
			l++;
		}
	}
	printf("%lld %lld\n", mx, val);
	
	
	return 0;
}
