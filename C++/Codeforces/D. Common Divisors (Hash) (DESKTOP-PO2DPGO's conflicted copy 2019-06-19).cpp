#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define MAXN 100100
const ll AA = 1009;
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
	return (mul(hash, AA) + c)%MOD;
}

void buildPot(){
	for (int i = 0; i < MAXN; i++)
	{
		pot[i] = i ? mul(pot[i-1], AA) : 1LL;
	}
}

struct Hash{
	string s;
	ll hashNormal, hashInvertida;
	ll accNormal[MAXN], accInvertida[MAXN];
	
	Hash(){}
	Hash(string _s){
		s = _s;
	}
	
	void build(){
		accNormal[0] = 0LL;
		for (int i = 1; i <= (int)s.size(); i++){
			accNormal[i] = add(accNormal[i-1], s[i-1]-'a'+1);
		}
		hashNormal = accNormal[(int)s.size()];
		
		accInvertida[s.size()] = 0LL;
		for (int i = s.size()-1; i >= 0; i--){
			accInvertida[i] = add(accInvertida[i+1], s[i]-'a'+1);
		}
		hashInvertida = accInvertida[0];
		
	}
	
	ll getRangeNormal(int l, int r){//pega a hash da substring (l, r) na string normal (abcd - [0, 2] = abc)
		if(l>r) return 0LL;
		ll ans = (accNormal[r+1] - mul(accNormal[l], pot[r-l+1]))%MOD;
		return normalize(ans);
	}
	
	ll getRangeInvertido(int l, int r){//pega a hash da substring (l, r) na string invertida (abcd - [0, 2] = cba)
		if(l>r) return 0LL;
		ll ans = (accInvertida[l] - mul(accInvertida[r+1], pot[r-l+1]))%MOD;
		return normalize(ans);
	}
};

Hash A, B;

int ok(int tam){
	int l = 0, r = tam-1;
	ll h = A.getRangeNormal(l, r);
	
	while (r < (int)A.s.size())
	{
		if(A.getRangeNormal(l, r) != h) return 0;
		l += tam;
		r += tam;
	}
	
	l = 0;
	r = tam-1;
	
	while (r < (int)B.s.size())
	{
		if(B.getRangeNormal(l, r) != h) return 0;
		l += tam;
		r += tam;
	}
	
	return 1;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	buildPot();
	
	string a, b;
	
	
	cin >> a >> b;
	A = Hash(a);
	A.build();
	B = Hash(b);
	B.build();
	
	int szA = (int)a.size();
	int szB = (int)b.size();
	int lim;
	lim = sqrt(szA);
	
	set<int> divA, divAB;
	
	for (int i = 1; i <= lim; i++)
	{
		if(szA%i == 0){
			divA.insert(i);
			divA.insert(szA/i);
		}
	}
	
	lim = sqrt(szB);
	for (int i = 1; i <= lim; i++)
	{
		if(szB%i == 0){
			if(divA.count(i)) divAB.insert(i);
			if(divA.count(szB/i)) divAB.insert(szB/i);
		}
	}
	
	int ans = 0;
	for (auto i : divAB)
	{
		ans += ok(i);
	}
	cout << ans << "\n";
	
	return 0;
}
