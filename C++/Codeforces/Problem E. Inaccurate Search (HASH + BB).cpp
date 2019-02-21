//~ http://codeforces.com/group/eqgxxTNwgd/contest/101245/attachments

#include <bits/stdc++.h>

#define MAXN 1000100
using namespace std;
typedef long long int ll;
const ll A = 1009;
const ll MOD = 9LL + 1e18;
ll pot[MAXN];

ll normalize(ll r){
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ll((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	return normalize(r);
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

void buildPot(){
	for (int i = 0; i < MAXN; i++)
	{
		pot[i] = i ? mul(pot[i-1], A) : 1LL;
	}
}

struct Hash{
	string s;
	ll hashNormal;
	vector<ll> accNormal;
	
	Hash(){}
	Hash(string _s){
		s = _s;
		accNormal.resize((int)s.size()+1);
	}
	
	void build(){
		accNormal[0] = 0LL;
		for (int i = 1; i <= (int)s.size(); i++){
			accNormal[i] = add(accNormal[i-1], s[i-1]-'a'+1);
		}
		hashNormal = accNormal[(int)s.size()];
	}
	
	ll getRangeNormal(int l, int r){//pega a hash da substring (l, r) na string normal (abcd - [0, 2] = abc)
		if(l>r) return 0LL;
		ll ans = (accNormal[r+1] - mul(accNormal[l], pot[r-l+1]))%MOD;
		return normalize(ans);
	}
};

Hash hs, ht;

int getLenMismatch(int l, int r){
	int lo, hi, mid;
	int ansL = -1e9, ansR = 1e9;
	
	lo = 1;
	hi = r - l + 1;
	
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		if(hs.getRangeNormal(l, l+mid-1) == ht.getRangeNormal(0, mid-1)){
			ansL = max(ansL, mid-1);
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	if(ansL == -1e9) ansL=-1;
	ansL++;
	
	lo = 1;
	hi = r - l + 1;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		
		if(hs.getRangeNormal(r-mid+1, r) == ht.getRangeNormal((int)ht.s.size()-1-mid+1, (int)ht.s.size()-1)){
			ansR = min(ansR, (int)ht.s.size()-1-mid+1);
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	
	if(ansR == 1e9) ansR=(int)ht.s.size();
	ansR--;
	
	return ansR - ansL + 1;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s, t;
	int k;
	vector<int> ans;
	
	buildPot();
	cin >> s >> t >> k;
	
	hs = Hash(s);
	ht = Hash(t);
	hs.build();
	ht.build();
	
	int l = 0, r = (int)t.size()-1;
	
	while (r < (int)s.size()){
		if(hs.getRangeNormal(l, r) == ht.hashNormal)
			ans.push_back(l+1);
		else if(getLenMismatch(l, r) <= k)
			ans.push_back(l+1);
			
		l++;
		r++;
	}
	
	cout << (int)ans.size() << "\n";
	if((int)ans.size() > 0){
		for (int i = 0; i < (int)ans.size(); i++)
		{
			if(i) cout << " ";
			cout << ans[i];
		}
		cout << "\n";
	}
	
	return 0;
}
