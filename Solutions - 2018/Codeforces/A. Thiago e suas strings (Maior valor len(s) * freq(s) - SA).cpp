#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
typedef long long int ll;

struct SuffixArray{
	int cnt[MAXN], tmpsa[MAXN], sa[MAXN], tmprk[MAXN], rk[MAXN], n, inv[MAXN], lcp[MAXN];
	string s;
	SuffixArray(){}
	SuffixArray(string _s){
		s = _s;
		n = (int)s.size();
	}
	
	void radix(int  k){
		
		memset(cnt, 0, sizeof cnt);
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

int l[MAXN], r[MAXN];

int main(){
	string s;
	cin >> s;
	s += '$';
	
	SuffixArray SA(s);
	SA.build_SA();
	SA.build_lcp();
	
	stack<int> p;
	for (int i = 0; i < SA.n; i++)
	{
		//~ cout << SA.lcp[i] << " ";
		while(p.size() > 0 && SA.lcp[p.top()] >= SA.lcp[i]) p.pop();
		l[i] = p.size() ? p.top() - 1 : -1;
		p.push(i);
	}
	//~ cout << endl;
	
	while(p.size()) p.pop();
	
	int ans = 0;
	for (int i = SA.n - 1; i >= 0; i--)
	{
		while(p.size() > 0 && SA.lcp[p.top()] >= SA.lcp[i]) p.pop();
		r[i] = p.size() ? p.top() - 1 : SA.n - 1;
		p.push(i);
		
		ans = max(ans, SA.lcp[i] * (r[i] - l[i]));
	}
	
	//~ if(ans == 0) ans = s.size() - 1;
	cout << max(ans, (int)s.size()-1) << "\n";

	//~ for (int i = 0; i < SA.n; i++)
		//~ cout << l[i] << " ";
	//~ cout << endl;
	//~ for (int i = 0; i < SA.n; i++)
		//~ cout << r[i] << " ";
	//~ cout << endl;
	
	return 0;
}
