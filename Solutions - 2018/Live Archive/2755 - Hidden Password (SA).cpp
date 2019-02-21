#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010

struct SuffixArray{
	string s;
	int lcp[MAXN], sa[MAXN], rk[MAXN], tmpsa[MAXN], tmprk[MAXN], cnt[MAXN], inv[MAXN], n;
	SuffixArray(){}
	SuffixArray(string _s){
		s = _s;
		n = (int)s.size();
	}
	
	void radix(int k){
		int pos;
		int mx = max(300, n);
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < n; i++)
		{
			pos = (i + k) < n ? rk[i + k] : 0;
			cnt[pos]++;
		}
		
		for (int i = 1; i < mx; i++)
			cnt[i] += cnt[i-1];
		
		for (int i = n-1; i >= 0; i--)
		{
			pos = sa[i] + k < n ? rk[sa[i] + k] : 0;
			tmpsa[--cnt[pos]] = sa[i]; 
		}
		
		for (int i = 0; i < n; i++)
			sa[i] = tmpsa[i];
		
	}
	
	void buildSA(){
		for (int i = 0; i < n; i++)
		{
			sa[i] = i;
			rk[i] = s[i];
		}
		
		for (int k = 1; k < n; k *= 2)
		{
			radix(k);
			radix(0);
			
			tmprk[sa[0]] = 0;
			int r = 0;
			for (int i = 1; i < n; i++)
			{
				if(!(rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] == rk[sa[i-1]+k])) r++;
				tmprk[sa[i]] = r;
			}
			
			for (int i = 0; i < n; i++)
				rk[i] = tmprk[i];
			
			if(rk[sa[n-1]] == n-1) break;
		}
		
		//~ for (int i = 0; i < n; i++)
		//~ {
			//~ cout << sa[i] << " " << s.substr(sa[i]) << endl;
		//~ }
		
	}
	
	void buildLCP(){
		
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

int main(){
	string s;
	int tc, n;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		cin >> s;
		int sz = s.size();
		s = s + s + "$";
		SuffixArray SA(s);
		SA.buildSA();
		SA.buildLCP();
		
		int pos;
		//~ printf("s.size() = %d    sz = %d\n", s.size(), sz);
		for (int i = 0; i < s.size(); i++)
		{
			if(s.size() - SA.sa[i] > sz){
				pos = i;
				break;
			}
		}
		
		//~ printf("pos = %d\n", pos);
		while(pos+1 < s.size() && SA.lcp[pos+1] >= sz)
			pos++;
		
		cout << SA.sa[pos] << "\n";
	}
	
	
	return 0;
}
