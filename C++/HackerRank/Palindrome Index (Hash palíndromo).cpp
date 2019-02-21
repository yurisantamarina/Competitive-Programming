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
const ll A = 1009;
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

string s;
ll hp[MAXN];
ll hs[MAXN];
ll pot[MAXN];

int getTam(int l, int r){
	return r-l+1;
}

ll getP(int l, int r){
	return (hp[r+1]+MOD - mul(hp[l], pot[r-l+1]))%MOD;
}

ll getS(int L, int R){
	int l = s.size()-R-1;
	int r = s.size()-L-1;
	return (hs[r+1]+MOD - mul(hs[l], pot[r-l+1]))%MOD;
}

bool palindromo(int idx){
	ll pref, suf;
	if(idx==0){
		pref = getP(idx+1, s.size()-1);
		//~ oioi;
	}else if(idx==s.size()-1){
		pref = getP(0, idx-1);
	}else{
		pref = (mul(pot[getTam(idx+1, s.size()-1)], getP(0, idx-1))%MOD + getP(idx+1, s.size()-1))%MOD;
	}
	
	if(idx==0){
		suf = getS(idx+1, s.size()-1);
	}else if(idx==s.size()-1){
		suf = getS(0, idx-1);
	}else{
		suf = (getS(0, idx-1) + mul(pot[getTam(0, idx-1)], getS(idx+1, s.size()-1))%MOD)%MOD;
	}
	
	//~ while(pref<0) pref+=MOD;
	//~ while(pref>=MOD) pref-=MOD;
	
	//~ while(suf<0) suf+=MOD;
	//~ while(suf>=MOD) suf-=MOD;
	
	//~ cout << "idx = " << idx << "  pref = " << pref << "  suf = " << suf << endl;
	
	return pref==suf;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	pot[0] = 1LL;
	for(int i = 1; i < MAXN; i++)
		pot[i] = mul(pot[i-1], A);
	
	int t;
	cin >> t;
	while (t--)
	{
		cin >> s;
		hp[0] = 0LL;
		for(int i = 1; i <= s.size(); i++){
			hp[i] = add(hp[i-1], s[i-1]-'a'+1);
			//~ cout << hp[i] << "\n";
		}
		//~ cout << endl;
		reverse(s.begin(), s.end());
		
		hs[0] = 0LL;
		for(int i = 1; i <= s.size(); i++){
			hs[i] = add(hs[i-1], s[i-1]-'a'+1);
			//~ cout << hs[i] << "\n";
		}
		reverse(s.begin(), s.end());
		if(hp[s.size()] == hs[s.size()]){
			cout << "-1\n";
		}else{
			int ans = -1;
			for (int i = 0; i < s.size(); i++)
			{
				if(palindromo(i)){
					ans = i;
					break;
				}
			}
			cout << ans << "\n";
		}
	}
	
	
	return 0;
}
