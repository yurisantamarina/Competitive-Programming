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

ll hashP[5010];
ll hashS[5010];
ll pot[5010];
int dp[5010][5010];
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
	
int palindromo(int l, int r){
	return getP(l, r) == getS(l, r);
	
}

int solve(int l, int r){
	if(l>r) return dp[l][r] = 0;
	if(l==r) return dp[l][r] = 1;
	if(dp[l][r]!=-1) return dp[l][r];
	int ans = palindromo(l, r) + solve(l+1, r) + solve(l, r-1) - solve(l+1, r-1);
	return dp[l][r] = ans;
}



int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	memset(dp, -1, sizeof dp);
	cin >> s;
	pot[0] = 1LL;
	for(int i = 1; i < 5010; i++)
		pot[i] = mul(pot[i-1], A);
	
	hashP[0] = 0LL;
	for (int i = 1; i <= s.size(); i++)
		hashP[i] = add(hashP[i-1], s[i-1]-'a'+1);
	
	hashS[s.size()] = 0LL;
	for (int i = s.size()-1; i >= 0; i--)
		hashS[i] = add(hashS[i+1], s[i]-'a'+1);
	
	//~ for (int i = 0; i < s.size()+1; i++)
	//~ {
		//~ cout << hashP[i] << " ";
	//~ }
	//~ cout << endl;
	//~ for (int i = 0; i < s.size()+1; i++)
	//~ {
		//~ cout << hashS[i] << " ";
	//~ }
	//~ cout << endl;
	
	//~ cout << getP(1,3) << " "  << getS(1,3) << endl;
	int q;
	cin >> q;
	int l, r;
	while (q--)
	{
		cin >> l >> r;
		l--; r--;
		cout << solve(l, r) << "\n";
	}
	
	
	
	return 0;
}

