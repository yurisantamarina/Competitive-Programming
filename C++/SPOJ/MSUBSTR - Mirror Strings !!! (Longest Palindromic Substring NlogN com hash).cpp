#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 3010

const ll A = 33;
const ll MOD = 9LL + 1e18;

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ll((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

ll hPref[MAXN];
ll hSuff[MAXN];
ll pot[MAXN];
string entrada;

ll getP(int l, int r){
	ll ans = (hPref[r+1] - mul(hPref[l], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

ll getS(int L, int R){
	int l = entrada.size() - R - 1;
	int r = entrada.size() - L - 1;
	//~ cout << l << " " << r << endl;
	ll ans = (hSuff[r+1] - mul(hSuff[l], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	for (int i = 0; i < MAXN; i++)
		pot[i] = i ? mul(pot[i-1], A) : 1;
	
	int n;
	cin >> n;
	
	while(n--){
		cin >> entrada;
		hPref[0] = 0LL;
		for (int i = 1; i <= entrada.size(); i++)
		{
			hPref[i] = add(hPref[i-1], entrada[i-1]-'a'+1);
		}
		
		hSuff[0] = 0LL;
		for (int j = 1, i=entrada.size()-1; j <= entrada.size(); j++, i--)
		{
			hSuff[j] = add(hSuff[j-1], entrada[i]-'a'+1);
		}
		
		int ans = 1;
		int l=0, r=0;
		string saida;
		for (int i = 0; i < entrada.size(); i++)
		{
			int lo, hi, mid;
			
			//impar
			lo = 1;
			hi = entrada.size();
			int cnt = 0;
			while (cnt++<13)
			{
				mid = (lo+hi)/2;
				//~ cout << "mid = " << mid << endl;
				if(i+mid < entrada.size() && i-mid >= 0){
					if(getP(i+1, i+mid) == getS(i-mid, i-1)){
						lo = mid;
						if(2*mid+1 > ans){
							ans = 2*mid + 1;
							l = i-mid;
							r = i+mid;
						}
					}else{
						hi = mid;
					}
				}else{
					hi = mid;
				}
			}
			//~ cout << endl;
			//~ if(i==0) continue;
			
			
			//par
			lo = 1;
			hi = entrada.size();
			cnt = 0;
			
			while (cnt++<13)
			{
				mid = (lo+hi)/2;
				if(i+mid-1 < entrada.size() && i-mid >= 0){
					if(getP(i, i+mid-1) == getS(i-mid, i-1)){
						lo = mid;
						if(2*mid > ans){
							ans = 2*mid;
							l = i-mid;
							r = i+mid-1;
						}
					}else{
						hi = mid;
					}
				}else{
					hi = mid;
				}
			}
		}
		
		//~ reverse()
		//~ cout << ans << " " << entrada.substr(l, r-l+1) << endl;
		int tam = r-l+1;
		int cnt = 0;
		
		for (int i = 0; i < entrada.size(); i++)
		{
			if(i+tam > entrada.size()) break;
			if(getP(i, i+tam-1) == getS(i, i+tam-1))
				cnt++;
				
		}
		
		
		cout << ans << " " << cnt << "\n";
	}
	
	
	
	return 0;
}
