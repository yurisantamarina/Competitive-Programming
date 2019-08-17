#include <bits/stdc++.h>
 
using namespace std;
#define MAXN 501010
 
struct SuffixArray{
	int n;
	vector<int> cnt, tmpsa, sa, tmprk, rk, inv, lcp;
	string s;
	SuffixArray(){}
	SuffixArray(string _s){
		s = _s;
		n = (int)s.size();
		
		cnt.resize(max(300, n+3));
		tmpsa.resize(max(300, n+3));
		sa.resize(max(300,  n+3));
		tmprk.resize(max(300, n+3));
		rk.resize(max(300,  n+3));
		inv.resize(max(300, n+3));
		lcp.resize(max(300,  n+3));
	}
	
	void radix(int  k){
		for (int i = 0; i < cnt.size(); i++)
			cnt[i] = 0;
		
		int maxi = max(300, n);
		
		for(int  i=0; i<n; i++){
			cnt[ (i+k)<n ?  rk[i+k] : 0 ]++;
		}
		
		for(int  i=1; i<maxi; i++) cnt[i]+=cnt[i-1];
		
		for(int  i=n-1; i>=0; i--){
			tmpsa[ --cnt[ ( sa[i]+k ) < n   ?  rk[sa[i]+k] : 0 ] ] = sa[i];
		}
		for(int  i=0; i<n; i++) sa[i] = tmpsa[i];
	}
 
 
	void build_SA(){
		
		for(int  i=0; i<n; i++){
			rk[i] = s[i];
			sa[i] = i;
		}
		
		for(int  k=1; k<n; k<<=1){
			
			radix(k);
			radix(0);
			
			tmprk[sa[0]] = 0;
			int  r = 0;
			for(int  i=1; i<n; i++){
				tmprk[sa[i]] = (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] == rk[sa[i-1]+k]) ? r : ++r;
			}
			
			for(int  i=0; i<n; i++){
				rk[sa[i]] = tmprk[sa[i]];
			}
			
			if(rk[sa[n-1]] == n-1) break;
		}
		
	}
 
	void build_lcp(){
		
		for(int  i=0; i<n; i++){
			inv[sa[i]] = i;
		}
		int  L=0;
		for(int  i=0; i<n; i++){
			if(inv[i] == 0){
				lcp[inv[i]] = 0;
				continue;
			}
			int  prev = sa[inv[i]-1];
			while(i+L<n && prev+L<n && s[i+L] == s[prev+L]) L++;
			
			lcp[inv[i]] = L;
			L = max(L-1, 0);
		}
	}
};
 
string s;
 
int main(){
	cin >> s;
	s += '$';
	SuffixArray SA(s);
	SA.build_SA();
	SA.build_lcp();
	
	int ans = 0;
	for (int i = 1; i < s.size(); i++)
		if(SA.lcp[i] > SA.lcp[ans] && SA.lcp[i] >= 3)
			ans = i;
	if(ans == 0) cout << "*\n";
	else cout << SA.s.substr(SA.sa[ans], SA.lcp[ans]) << "\n";
	
	
	return 0;
}
