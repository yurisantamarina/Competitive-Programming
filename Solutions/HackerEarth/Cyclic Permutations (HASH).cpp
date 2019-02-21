#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 100100
const ll A = 3;
const ll MOD = 9LL + 1e18;

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

ll pot[MAXN];

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	pot[0] = 1LL;
	for(int i = 1; i < MAXN; i++)
		pot[i] = mul(pot[i-1], A);
	
	int t;
	string a, b;
	cin >> t;
	while (t--)
	{
		cin >> a >> b;
		b += b;
		ll hashA = 0LL;
		for (int i = 0; i < a.size(); i++)
		{
			hashA = add(hashA, a[i]-'0'+1);
		}
		
		ll hashW = 0LL;
		for (int i = 0; i < a.size(); i++)
		{
			hashW = add(hashW, b[i]-'0'+1);
		}
		
		//~ cout << a << "\n" << b << endl; 
		int ans = 0;
		if(hashW==hashA) ans++;
		int sz = a.size();
		for (int i = a.size(); i < b.size()-1; i++)
		{
			hashW = (hashW - mul(b[i-sz]-'0'+1, pot[sz-1]))%MOD;
			//~ cout << "tira " << i-sz << "  adiciona " << i << "\n";
			hashW = mul(hashW, A);
			hashW += b[i]-'0'+1;
			hashW %= MOD;
			//~ cout << "hashA = " << hashA << "  hashW = " << hashW << endl;
			if(hashW==hashA) ans++;
		}
		cout << ans << "\n";
	}
	
	
	
	
	return 0;
}
