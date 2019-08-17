#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;

const ll A = 1009;
const ll MOD = 9LL + 1e18;

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ll((long double)a*b/MOD);
	ll r = ll(a*b - MOD*q);
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

int n;
ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

ll hashP[11][50010];
ll hashS[11][50010];
ll pot[50010];
string s;

ll getP(int l, int r, int idx){
	ll ans = (hashP[idx][r+1] - mul(hashP[idx][l], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

ll getS(int l, int r, int idx){
	ll ans = (hashS[idx][l] - mul(hashS[idx][r+1], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

bool palind(int l, int r, int idx){
	if(l==r) return true;
	return getP(l, r, idx) == getS(l, r, idx);
}
vector<string> v;

bool ok(int tam){
	set<ll> s[10];
	map<ll, int> mapa;
	
	int l, r;
	ll hash;
	for (int idx = 0; idx < n; idx++)
	{
		l = 0, r = tam-1;
		//~ oioi;
		while (r < (int)v[idx].size())
		{
			hash = getP(l, r, idx);
			
			if(palind(l, r, idx)){
			
				if(s[idx].count(hash) == 0){
					mapa[hash]++;
					if(mapa[hash]==n){
						//~ printf("idx = %d l = %d  r = %d\n", idx, l, r);
						return true;
					}
					s[idx].insert(hash);
				}
			}
			
			l++;
			r++;
		}
		
	}
	//~ oioi;
	return false;
}

int main () {
	pot[0] = 1LL;
	for(int i = 1; i < 50010; i++)
		pot[i] = mul(pot[i-1], A);
	while (cin >> n)
	{
		int mn = 1e9;
		v.clear();
		for (int idx = 0; idx < n; idx++)
		{
			cin >> s;
			v.pb(s);
			hashP[idx][0] = 0LL;
			for (int i = 1; i <= s.size(); i++)
				hashP[idx][i] = add(hashP[idx][i-1], s[i-1]-'A'+1);
			
			mn = min(mn, (int)s.size());
			hashS[idx][s.size()] = 0LL;
			for (int i = s.size()-1; i >= 0; i--)
				hashS[idx][i] = add(hashS[idx][i+1], s[i]-'A'+1);
		}
		int lo = 1, hi = mn, mid, ans=0;
		//~ printf("mn = %d\n", mn);
		int cnt = 0;
		while (cnt++ < 20 && lo <= hi)
		{
			mid = (lo+hi)/2;
			//~ oioi;
			//~ printf("Testando %d\n", mid);
			if(mid%2==0){
				if(ok(mid)){
					ans = mid;
					lo = mid+1;
				}else{
					if(ok(mid+1)){
						ans = mid;
						lo = mid+1;
					}else{
						hi = mid-1;
					}
				}
			}else{
				//~ mid++;
				if(ok(mid)){
					ans = mid;
					lo = mid+1;
				}else{
					if(ok(mid+1)){
						ans = mid;
						lo = mid+1;
					}else{
						hi = mid-1;
					}
				}
			}
		}
		cout << ans << "\n";
		
	}
	
	
	
	
	
	
	
	
	
	return 0;
}
