#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long int ll;
#define MAXN 200010
#define pb push_back
#define F first
#define S second
#define mp make_pair
ll inf = 1000000000000LL;

struct reta{
	ll a, b;
	reta(){}
	reta(ll _a, ll _b){
		a = _a;
		b = _b;
	}
	
	ll getVal(ll x){
		return a*x+b;
	}
};

struct cht{
	vector<reta> ch;
	int sz;
	cht(){
		sz = 0;
	}
	
	bool pode(reta ant, reta top, reta at){
		return (ant.b-at.b)*(top.a-ant.a) <= (ant.b-top.b)*(at.a-ant.a);
	}
	
	void add(reta r){
		//~ printf("inserindo y = %lldx + %lld\n", r.a, r.b);
		while (sz > 1 && pode(ch[sz-2], ch[sz-1], r))
		{
			sz--;
			ch.pop_back();
		}
		sz++;
		ch.pb(r);
	}
	
	ll query(ll x){
		int lo = 0, hi = sz-1, mid, ans=0;
		while (lo <= hi)
		{
			mid = (lo+hi)/2;
			if(mid+1 == sz) return ch[mid].getVal(x);
			if(ch[mid].getVal(x) < ch[mid+1].getVal(x)){
				lo = mid+1;
			}else{
				hi = mid-1;
				ans = mid;
			}
		}
		
		return ch[ans].getVal(x);
	}
};

ll v[MAXN], n;
ll dp[MAXN];
ll prod[MAXN];
ll sum[MAXN];

void build(){
	sum[0] = 0LL;
	prod[0] = 0LL;
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i-1] + v[i];
		prod[i] = prod[i-1] + v[i]*ll(i);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
	}
	
	build();
	
	dp[0] = 0LL;
	
	cht CH;
	//~ cout << "oi\n";
	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		CH.add(reta(i-1, sum[i-1]*(i-1) - prod[i-1]));
		//~ printf("consultando sum[%d] = %lld\n", i, -sum[i]);
		dp[i] = CH.query(-sum[i]) + prod[i];
		ans = max(ans, dp[i]);
		
		//~ cout << "dp[" << i << "] = " << dp[i] << endl;
	}
	cout << ans << "\n";
	
	
	
	return 0;
}
