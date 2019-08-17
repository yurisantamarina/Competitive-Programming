#include <bits/stdc++.h>

using namespace std;
#define MAXN 501010
#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long int ll;
struct SuffixArray{
	int n;
	vector<int> cnt, tmpsa, sa, tmprk, rk, inv, lcp;
	vector<int> s;
	SuffixArray(){}
	SuffixArray(vector<int> &_s){
		s = _s;
		n = (int)s.size();
		
		cnt.resize(max(350, n+3));
		tmpsa.resize(max(350, n+3));
		sa.resize(max(350,  n+3));
		tmprk.resize(max(350, n+3));
		rk.resize(max(350,  n+3));
		inv.resize(max(350, n+3));
		lcp.resize(max(350,  n+3));
	}
	
	void radix(int  k){
		for (int i = 0; i < cnt.size(); i++)
			cnt[i] = 0;
		
		int maxi = max(350, n);
		
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

int MOD = 1000000007;
vector<int> v[MAXN], pos[MAXN];

int exp(int base, int e){
	if(e == 0) return 1LL;
	int aux = exp(base, e / 2);
	aux = ((ll)aux * (ll)aux) % MOD;
	if(e & 1) aux = ((ll)aux * (ll)base) % MOD;
	return aux;
}

SuffixArray SA;
vector<int> s;
int ptr[MAXN], mapa[MAXN], n;

int solve(){
	for (int i = 0; i < SA.n; i++)
		mapa[SA.sa[i]] = i;
	
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	for (int i = 0; i < n; i++)
		pq.push(mp(mapa[pos[i][0]], i));
	
	vector<int> saida;
	
	pair<int, int> tp;
	while(!pq.empty()){
		tp = pq.top();
		pq.pop();
		saida.pb(v[tp.S][ptr[tp.S]]);
		ptr[tp.S]++;
		if(ptr[tp.S] == (int)v[tp.S].size()) continue;
		
		pq.push(mp(mapa[pos[tp.S][ptr[tp.S]]], tp.S));
	}
	int ans = 0;
	for (int i = 0; i < saida.size(); i++)
		ans = ((ll)ans + (ll)saida[i] * exp(365, (int)saida.size() - i)) % MOD;
	return ans;
}

int main(){
	int q, x;
	scanf("%d", &n);
	
	int cnt = 0;
	for (int j = 0; j < n; j++)
	{
		scanf("%d", &q);
		for (int i = 0; i < q; i++)
		{
			scanf("%d", &x);
			v[j].pb(x);
			pos[j].pb(cnt++);
			s.pb(x);
		}
		s.pb(301);
		cnt++;
	}
	
	SA = SuffixArray(s);
	SA.build_SA();
	SA.build_lcp();
	
	printf("%d\n", solve());
	
	return 0;
}
