#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
typedef long long int ll;

ll bit[MAXN];
ll v[MAXN];

void update(ll please, ll val){
	for(please; please < MAXN; please += please & -please){
		bit[please] += val;
	}
}

ll query(ll please){
	ll ans = 0;
	for(please; please > 0; please -= please & -please){
		ans += bit[please];
	}
	return ans;
}

int main(){
	ll n, op, val, qtd;
	scanf("%lld", &n);
	ll cnt = 2;
	ll sum = 0;
	
	for (ll i = 0; i < n; i++)
	{
		scanf("%lld", &op);
		
		if(op == 1){
			
			scanf("%lld %lld", &qtd, &val);
			sum += (qtd * val);
			update(1, val);
			update(qtd+1, -val);
			
		}else if(op == 2){
			
			scanf("%lld", &val);
			sum += val;
			val = val - query(cnt);
			v[cnt++] = val;
			
		}else{
			
			cnt--;
			val = v[cnt] + query(cnt);
			sum -= val;
			v[cnt] = 0;
			
		}
		
		printf("%.6lf\n", (sum * 1.0) / (cnt-1));
	}
	
	
	
	return 0;
}
