//~ http://codeforces.com/group/eqgxxTNwgd/contest/101245

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
	ll r = a*b - MOD*q;
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

ll hashP[50010];
ll hashS[50010];
ll pot[50010];
string s;

ll getP(int l, int r){
	ll ans = (hashP[r+1] - mul(hashP[l], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

ll getS(int l, int r){
	ll ans = (hashS[l] - mul(hashS[r+1], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

int main () {
	string s2;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> s;
	cin >> s2;
	ll hash2 = 0LL;
	
	for (int i = 0; i < s2.size(); i++)
	{
		hash2 = add(hash2, s2[i]-'a'+1);
	}
	
	
	pot[0] = 1LL;
	for(int i = 1; i < 50010; i++)
		pot[i] = mul(pot[i-1], A);
	
	hashP[0] = 0LL;
	for (int i = 1; i <= s.size(); i++)
		hashP[i] = add(hashP[i-1], s[i-1]-'a'+1);
	
	hashS[s.size()] = 0LL;
	for (int i = s.size()-1; i >= 0; i--)
		hashS[i] = add(hashS[i+1], s[i]-'a'+1);
	
	if(s==s2){
		cout << "Yes\n0\n";
		return 0;
	}
	
	int ans = -1;
	ll fst, snd;
	for (int k = 1; k <= s.size(); k++)
	{
		fst = (mul(getP(k, s.size()-1), pot[k]) + getS(0, k-1))%MOD;
		//~ cout << "pegando " << s.substr(k, s.size()-k) << " + " << s.substr(0, k) << endl;
		if(fst==hash2){
			cout << "Yes\n";
			cout << k << "\n";
			return 0;
		}
	}
	cout << "No\n";
	
	
	
	return 0;
}
