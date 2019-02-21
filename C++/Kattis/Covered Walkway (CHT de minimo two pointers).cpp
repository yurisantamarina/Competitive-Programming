#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long int ll;
#define MAXN 1000010
#define pb push_back
ll inf = 1000000000000000LL;
ll v[MAXN];
ll dp[MAXN];

//~ dp[0] = 0;
//~ dp[i] = min(dp[j] + c + (v[i] - v[j+1])²);
//~ expandindo fica:
//~ dp[i] = c + min(dp[j] + v[i]² - 2*v[i]*v[j+1] + v[j+1]²);
//~ dp[i] = c + v[i]² + min(-2*v[j+1]*v[i] + (dp[j] + v[j+1]²));
//~ y = 						a    *x    +       b

struct reta{
	ll a, b;
	reta(){}
	reta(ll _a, ll _b){
		a = _a;
		b = _b;
	}
	
	ll getVal(ll x){
		return a*x + b;
	}
};

struct cht{
	vector<reta> ch;
	int sz, ptr;
	cht(){
		sz = 0;
		ptr = 0;
	}
	
	bool pode(reta ant, reta top, reta at){
		return (ant.b - at.b) * (top.a - ant.a) <= (ant.b - top.b) * (at.a - ant.a);
	}
	
	void add(reta r){
		
		while (sz > 1 && pode(ch[sz-2], ch[sz-1], r))
		{
			sz--;
			ch.pop_back();
		}
		ch.pb(r);
		sz++;
		
	}
	
	ll query(ll x){
		
		while (ptr < sz)
		{
			if(ptr+1 == sz) break;
			if(ch[ptr].getVal(x) > ch[ptr+1].getVal(x)) ptr++;
			else{
				break;
			}
		}
		
		return ch[ptr].getVal(x);
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, c;
	cin >> n >> c;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
	}
	dp[0] = 0;
	cht CH;
	CH.add(reta(-2LL*v[1], dp[0] + v[1]*v[1]));
	
	for (int i = 1; i <= n; i++)
	{
		dp[i] = CH.query(v[i]);
		dp[i] += c + v[i]*v[i];
		
		if(i < n){
			CH.add(reta(-2LL*v[i+1], dp[i] + v[i+1]*v[i+1]));
		}
	}
	cout << dp[n] << "\n";
	
	
	
	return 0;
}
 
