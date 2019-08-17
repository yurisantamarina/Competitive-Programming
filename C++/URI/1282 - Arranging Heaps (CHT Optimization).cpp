#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long int ll;
#define MAXN 1010
#define pb push_back
ll inf = 1000000000000000LL;

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
	
	void reset(){
		ch.clear();
		sz = 0;
		ptr = 0;
	}
	
	bool pode(reta ant, reta top, reta at){
		return (ant.b - at.b)*(top.a - ant.a) <= (ant.b - top.b)*(at.a - ant.a);
	}
	
	void add(reta r){
		
		while (sz > 1 && pode(ch[sz-2], ch[sz-1], r))
		{
			ch.pop_back();
			sz--;
		}
		
		ch.pb(r);
		sz++;
	}
	
	ll query(ll x){
		if(sz == 0) return 0;
		while (ptr < sz)
		{
			if(ptr+1 == sz) break;
			if(ch[ptr].getVal(x) > ch[ptr+1].getVal(x)) ptr++;
			else break;
		}
		
		return ch[ptr].getVal(x);
	}
};

int n, k;
ll v[MAXN];
ll w[MAXN];
ll dp[MAXN][MAXN];
ll sumW[MAXN];
ll sumXW[MAXN];

void build(){
	sumW[0] = 0;
	sumXW[0] = 0;
	
	for (int i = 1; i <= n; i++)
	{
		sumW[i] = sumW[i-1] + w[i];
		sumXW[i] = sumXW[i-1] + v[i]*w[i];
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while(cin >> n >> k){
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i] >> w[i];
		}
		
		build();
		
		for (int i = 1; i <= n; i++)
		{
			dp[i][1] = v[i] * (sumW[i-1] - sumW[0]) - (sumXW[i-1] - sumXW[0]);
		}
		
		cht CH;
		
		for (int K = 2; K <= k ; K++)
		{
			CH.reset();
			for (int i = K-1; i <= n; i++)
			{
				dp[i][K] = CH.query(v[i]) + v[i]*sumW[i-1] - sumXW[i-1];
				CH.add(reta(-sumW[i], dp[i][K-1] + sumXW[i]));
			}
		}
		cout << dp[n][k] << "\n";
	}
	
	
	return 0;
}
 
