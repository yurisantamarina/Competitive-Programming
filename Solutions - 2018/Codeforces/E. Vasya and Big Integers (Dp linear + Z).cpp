#include <bits/stdc++.h>

using namespace std;
#define MAXN 2010101
#define MOD 998244353
typedef long long int ll;

ll dp[MAXN], acc[MAXN];


ll query(int l, int r){
	if(l > r) return 0;
	
	return ((ll)acc[l] - (ll)acc[r + 1] + (ll)MOD + (ll)MOD) % MOD;
}

vector<int> Z(string s){
	int n = (int)s.size();
	vector<int> z(n, 0), ans;
	int l = 0, r = 0, pos = -1;
	for (int i = 1; i < n; i++)
	{
		if(s[i] == '$') pos = i;
		if(i <= r) z[i] = min(z[i - l], r - i + 1);
		while(i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if(i + z[i] - 1 > r){
			l = i;
			r = i + z[i] - 1;
		}
	}
	
	for (int i = pos + 1; i < n; i++)
		ans.push_back(z[i]);
	
	return ans;
}

int main(){
	string S, L, R;
	cin >> S;
	cin >> L;
	cin >> R;
	
	int n = (int)S.size();
	int szL = (int)L.size();
	int szR = (int)R.size();
	
	vector<int> zl = Z(L + "$" + S);
	vector<int> zr = Z(R + "$" + S);

	int l, r, pref;
	dp[n] = 1;
	acc[n] = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		if(S[i] == '0'){
			dp[i] = L == "0" ? dp[i + 1] : 0;
			
		}else{
			if(i + szR - 1 >= n) r = n;
			else{
				r = i + szR - 1;
				pref = zr[i];
				
				if(pref == szR || S[i + pref] < R[pref]) r++;
			}
			
			if(i + szL - 1 >= n) l = n;
			else{
				l = i + szL - 1;
				pref = zl[i];
				
				if(pref < szL && S[i + pref] < L[pref]) l++;
			}
			
			dp[i] = query(l + 1, r);
		}
		
		acc[i] = (acc[i + 1] + dp[i]) % MOD;
	}
	printf("%lld\n", dp[0]);
	
	
	return 0;
}
