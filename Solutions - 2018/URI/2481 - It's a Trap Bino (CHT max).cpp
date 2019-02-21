#include <bits/stdc++.h>
 
using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
#define MAXN 1010
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
typedef long long int ll;
typedef long double ld;
ll INF = LLONG_MAX;
ll tc, x[101010], c[101010], dp[101010], n;


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
		if(sz==0) return 0;
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

 
int main(){
	fast;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> x[i] >> c[i];
		dp[0] = 0;
		
		cht CH;
		for (int i = 1; i <= n; i++){
			dp[i] = max(CH.query(x[i]), 0LL);
			CH.add(reta(x[i], dp[i] - x[i]*x[i] - c[i]));
		}
		
		dp[n] -= c[n];
		if(dp[n] > 0) cout << "Ganha " << dp[n] << "\n";
		else cout << "Perde " << -dp[n] << "\n";
	}
	
	
	
	return 0;
}
 
