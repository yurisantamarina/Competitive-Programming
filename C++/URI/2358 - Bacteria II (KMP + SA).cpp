#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long int ll;

struct SuffixArray{
	int cnt[MAXN], tmpsa[MAXN], sa[MAXN], tmprk[MAXN], rk[MAXN], n, inv[MAXN], lcp[MAXN];
	string s;
	SuffixArray(){}
	SuffixArray(string &_s){
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

string s[30], virus;
int dp[MAXN];

void change(int idx){
	stack<int> p;
	dp[0] = 0;
	p.push(0);
	
	string tmp = virus + "$" + s[idx];
	int id;
	for (int i = 1; i < (int)tmp.size(); i++)
	{
		id = dp[p.top()];
		while(id > 0 && tmp[id] != tmp[i])
			id = dp[id-1];
		if(tmp[id] == tmp[i]) id++;
		dp[i] = id;
		p.push(i);
		
		if(dp[i] == (int)virus.size()){
			for (int j = 0; j < (int)virus.size(); j++)
				p.pop();
		}
		
	}
	
	string tmp2 = "";
	while(p.size()){
		if(p.top() > virus.size()) tmp2 += tmp[p.top()];
		p.pop();
	}
	reverse(tmp2.begin(), tmp2.end());
	s[idx] = tmp2;
}

struct minqq{
	deque<int> dq;
	minqq(){
		dq.clear();
	}
	
	void add(int val){
		while(dq.size() > 0 && dq.back() > val) dq.pop_back();
		dq.push_back(val);
	}
	
	void del(int val){
		if(val == dq.front()) dq.pop_front();
	}
	
	int query(){
		return dq.front();
	}
};

int nxt[MAXN], f[30], diff = 0;
minqq minq;
SuffixArray SA;

void add(int pos){
	f[nxt[SA.sa[pos]]]++;
	if(f[nxt[SA.sa[pos]]] == 1) diff++;
	minq.add(SA.lcp[pos]);
}

void del(int pos){
	f[nxt[SA.sa[pos]]]--;
	if(f[nxt[SA.sa[pos]]] == 0) diff--;
	minq.del(SA.lcp[pos]);
}

char lixo[MAXN];

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int n;
	while(scanf("%d", &n) != EOF){
		memset(f, 0, sizeof f);
		memset(nxt, 0, sizeof nxt);
		diff = 0;
		for (int i = 0; i < n; i++){
			scanf(" %s", lixo);
			s[i] = lixo;
		}
		scanf(" %s", lixo);
		virus = lixo;
		
		for (int i = 0; i < n; i++)
			change(i);
		
		if(n == 1){
			//~ cout << s[0] << "\n";
			printf("%s\n", s[0].c_str());
			continue;
		}
		string todas = "";
		int separador = 32;
		for (int i = 0; i < n; i++)
		{
			todas += s[i];
			todas += char(separador++);
		}
		int cnt = n+1;
		for (int i = todas.size()-1; i >= 0; i--)
			nxt[i] = (todas[i] <= separador) ? --cnt : cnt;
		
		
		SA = SuffixArray(todas);
		SA.build_SA();
		SA.build_lcp();
		int l = 0, r = 0, ans = 0, idx = 0;
		minq = minqq();
		add(0);
		
		for (l = 0; l < SA.n; l++)
		{
			while(diff < n && r < SA.n) add(++r);
			del(l);
			int mn = minq.query();
			if(mn > ans){
				ans = mn;
				idx = l;
			}
		}
		
		printf("%s\n", SA.s.substr(SA.sa[idx], ans).c_str());
	}
	
	
	return 0;
}

