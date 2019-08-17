#include <bits/stdc++.h>

using namespace std;
#define MAXN 601010
#define LOG 20
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

SuffixArray SA;
int nxt[MAXN], dist[MAXN], l[MAXN], r[MAXN];

struct ST{
	ll v[MAXN][LOG];
	ST(){}
	void build(){
		int n = SA.n;
		for (int i = 0; i < n; i++)
			v[i][0] = (1LL << nxt[SA.sa[i]]);
		
		for (int j = 1; j < LOG; j++)
			for (int i = 0; i + (1 << j) - 1 <= n - 1; i++)
				v[i][j] = v[i][j-1] | v[i + (1 << (j - 1))][j-1];
	}
	ll get(int l, int r){
		int k = 31 - __builtin_clz(r - l + 1);
		return v[l][k] | v[r - (1 << k) + 1][k];
	}
};
ST st;

int solve(){
	st.build();
	stack<int> p;
	vector<ll> conj;
	for (int i = 0; i < SA.n; i++)
	{
		while(!p.empty() && SA.lcp[p.top()] >= SA.lcp[i])
			p.pop();
		l[i] = p.empty() ? -1 : p.top();
		p.push(i);
	}
	while(!p.empty())
		p.pop();
	for(int i = SA.n - 1; i >= 0; i--)
	{
		while(!p.empty() && SA.lcp[p.top()] >= SA.lcp[i])
			p.pop();
		r[i] = p.empty() ? SA.n : p.top();
		p.push(i);
		
		if(SA.lcp[i] > 0)
			conj.push_back(st.get(l[i], r[i] - 1));
		if(dist[SA.sa[i]] > SA.lcp[i] && (i == SA.n - 1 || dist[SA.sa[i]] > SA.lcp[i+1]))
			conj.push_back(1LL << nxt[SA.sa[i]]);
	}
	sort(conj.begin(), conj.end());
	int ans = 1;
	for (int i = 1; i < (int)conj.size(); i++)
		ans += (conj[i] != conj[i-1]);
	return ans;
}

string s[MAXN];

int main(){
	int n;
	string todas;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while(cin >> n, n){
		int separador = 0;
		todas = "";
		for (int i = 0; i < n; i++)
		{
			cin >> s[i];
			todas += s[i];
			todas += char(separador++);
		}
		int cnt = n+1;
		for (int i = (int)todas.size() - 1; i >= 0; i--)
		{
			if(todas[i] < separador){
				cnt--;
				dist[i] = 0;
			}else{
				dist[i] = dist[i+1] + 1;
			}
			nxt[i] = cnt;
		}
		
		SA = SuffixArray(todas);
		SA.build_SA();
		SA.build_lcp();
		cout << solve() << "\n";
	}
	
	return 0;
}

