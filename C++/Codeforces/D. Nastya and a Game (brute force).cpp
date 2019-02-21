#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
typedef long long int ll;
ll n, k, lst[MAXN], v[MAXN];

int main(){
	scanf("%lld %lld", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &v[i]);
		lst[i] = v[i] == 1 ? lst[i-1] : i;
	}
	
	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		ll j = i;
		ll sum = 0, prod = 1, falta;
		while(j > 0){
			if(v[j] == 1){
				if(prod % k == 0 && (prod / k) - sum > 0){
					falta = (prod / k) - sum;
					if(j - lst[j] >= falta)
						ans++;
				}
				sum += (j - lst[j]);
				j = lst[j];
			}else{
				if((long double)prod * v[j] >= 3e18) break;
				prod *= v[j];
				sum += v[j];
				j--;
				if(prod % sum == 0 && prod / sum == k)
					ans++;
			}
		}
	}
	
	printf("%lld\n", ans);
	
	
	return 0;
}
