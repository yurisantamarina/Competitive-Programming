#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 201010
#define pb push_back

ll A = 1009;
ll MOD = 1e18 + 9LL;
ll pot[MAXN];


ll normalize(ll h){
	while(h < 0) h += MOD;
	while(h >= MOD) h -= MOD;
	return h;
}

ll mul(ll a, ll b){
	ll q = ll((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	return normalize(r);
}

ll add(ll h, ll c){
	return (mul(h, A) + c)%MOD;
}

void buildPot(){
	pot[0] = 1LL;
	for (int i = 1; i < MAXN; i++)
		pot[i] = mul(pot[i-1], A);
}


struct Hash{
	vector<ll> acc;
	string s;
	Hash(){}
	Hash(string _s){
		s = _s;
	}
	void build(){
		acc.pb(0LL);
		for (int i = 1; i <= s.size(); i++){
			acc.pb(add(acc[i-1], s[i-1]-'a'+1));
		}
	}
	
	ll getRange(int l, int r){
		if(l > r) return 0LL;
		return normalize(acc[r+1] - mul(acc[l], pot[r-l+1]));
	}
};

string s, t;
Hash S, T;

bool solve(int l1, int r1, int l2, int r2){
	if(S.getRange(l1, r1) == T.getRange(l2, r2)){
		return true;
	}
	if((r1-l1+1)%2) return false;
	
	int mid1 = (l1+r1)/2;
	int mid2 = (l2+r2)/2;
	
	return (solve(l1, mid1, mid2+1, r2) && solve(mid1+1, r1, l2, mid2)) || (solve(l1, mid1, l2, mid2) && solve(mid1+1, r1, mid2+1, r2));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> s >> t;
	
	
	if((int)s.size()%2){
		if(s == t) cout << "YES\n";
		else cout << "NO\n"; 
		return 0;
	}
	buildPot();
	S = Hash(s);
	S.build();
	T = Hash(t);
	T.build();
	
	if(solve(0, s.size()-1, 0, s.size()-1)) cout << "YES\n";
	else cout << "NO\n";
	
	return 0;
}
