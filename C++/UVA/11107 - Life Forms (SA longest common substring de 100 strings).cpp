#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
typedef long long int ll;

struct SuffixArray{
	int cnt[MAXN], tmpsa[MAXN], sa[MAXN], tmprk[MAXN], rk[MAXN], n, inv[MAXN], lcp[MAXN];
	vector<int> s;
	SuffixArray(){}
	SuffixArray(vector<int> _s){
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

struct minqueue{
	deque<int> dq;
	
	minqueue(){
		dq.clear();
	}
	
	void add(int val){
		while(dq.size() > 0 && dq.back() > val) dq.pop_back();
		dq.push_back(val);
	}
	
	void del(int val){
		if(val == dq.front()) dq.pop_front();
	}
	
	int getMn(){
		return dq.size() ? dq.front() : 0;
	}
};

minqueue minq;
SuffixArray SA;
int lim, diff = 0, f[MAXN], nxt[MAXN];
vector<int> vet;

void add(int pos){
	f[nxt[SA.sa[pos]]]++;
	if(f[nxt[SA.sa[pos]]] == 1){
		diff++;
	}
	minq.add(SA.lcp[pos]);
}

void del(int pos){
	f[nxt[SA.sa[pos]]]--;
	if(f[nxt[SA.sa[pos]]] == 0) diff--;
	minq.del(SA.lcp[pos]);
}

bool ok(){
	return diff >= lim;
}

int main(){
	int tc;
	int n;
	bool fst = true;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(cin >> n, n){
		if(!fst) cout << "\n";
		fst = false;
		int l = 0, r = 0, ans = 0, mn, GAP = 100;
		string tmp;
		vector<int> s;
		memset(f, 0, sizeof f);
		diff = 0;
		
		
		int separador = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> tmp;
			
			for (int j = 0; j < tmp.size(); j++)
				s.pb(tmp[j] - 'a' + 1 + GAP);
			s.pb(separador++);
		}
		
		if(n == 1){
			cout << tmp << "\n";
			continue;
		}
		
		SA = SuffixArray(s);
		SA.build_SA();
		SA.build_lcp();
		
		int cnt = n+1;
		for (int i = SA.n-1; i >= 0; i--)
		{
			if(SA.s[i] <= 100) cnt--;
			nxt[i] = cnt;
		}
		lim = n/2 + 1;
		
		minq = minqueue();
		add(0);
		vet.clear();
		for (l = 0; l < SA.n; l++)
		{
			
			while(!ok() && r < SA.n){
				add(++r);
			}
			del(l);
			mn = minq.getMn();
			if(mn && mn >= ans){
				if(mn > ans) vet.clear();
				ans = mn;
				vet.pb(SA.sa[l]);
			}
		}
		
		
		set<string> saida;
		if(vet.size() == 0) cout << "?\n";
		else{
			string tmp="";
			for (int i = 0; i < vet.size(); i++)
			{
				tmp = "";
				for(int k = vet[i]; k < vet[i] + ans; k++){
					if(SA.s[k] >= 101) tmp += char(SA.s[k] - GAP - 1 + 'a');
					else tmp += '$';
				}
				saida.insert(tmp);
			}
			for(string it : saida)
				cout << it << "\n";
		}
	}
	
	return 0;
}
