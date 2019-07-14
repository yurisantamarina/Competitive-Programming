#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;

ll getPrice(ll n){
	ll price = 0;
	
	if(n>1000000){
		price = 100*2 + 9900*3 + 990000*5 + (n-1000000)*7;
	}else if(n>10000){
		price = 100*2 + 9900*3 + (n-10000)*5;
	}else if(n>100){
		price = 100*2 + (n-100)*3;
	}else{
		price = n*2;
	}
	
	return price;
}
int main(){
	ll n;
	
	ll dif;
	
	while (cin >> n >> dif)
	{
		if(n==0 && dif==0) break;
		ll lo = 0, hi = 1000000000;
		while (lo+1 < hi)
		{
			ll mid = (lo+hi)/2;
			if(getPrice(mid) >= n) hi = mid;
			else lo = mid;
		}
		
		ll consumo = hi;
		
		lo = 0; hi = consumo;
		ll ans = 0;
		
		//~ cout << "consumo = " << consumo << endl;
		while (lo+1 < hi)
		{
			ll mid = (lo+hi)/2;
			if(getPrice(consumo-mid) - getPrice(mid) == dif){
				ans = mid;
				break;
			}
			if(getPrice(consumo-mid) - getPrice(mid) > dif) lo = mid;
			else hi = mid;
		}
		cout << getPrice(ans) << "\n";
	}
	
	
	
	
	
}
