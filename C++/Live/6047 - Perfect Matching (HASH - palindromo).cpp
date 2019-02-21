#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const ll A = 1009;
const ll MOD = 1000000000000000009LL;

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

ll pot[520];
ll normal[1010];
ll inv[1010];
ll sz[1010];

ll getHash(string s, bool invertida){
	ll hash = 0LL;
	if(invertida){
		for(int i = s.size() - 1; i >= 0; i--)
			hash = add(hash, s[i]);
	}else{
		for (int i = 0; i < s.size(); i++)
			hash = add(hash, s[i]);
	}
	return hash;
}

/*
Exemplo: abac    aba

abac   : 1*3³ + 2*3² + 1*3¹ + 3*3⁰
aba    : 1*3² + 2*3¹ + 1*3⁰

abacaba: 1*3⁶ + 2*3⁵ + 1*3⁴ + 3*3³   +    1*3² + 2*3¹ + 1*3⁰
         =========================
         Essa parte é a hash de abac * 3^(size[aba])
=> hash[abacaba] = normal[abac]*pot[size[aba]] + normal[aba]


Calculando a invertida: aba    caba (não é a segunda+primeira, ainda é primeira+segunda, inverti as string apenas para calcular a hash invertida de primeira+segunda)
aba    : 1*3² + 2*3¹ + 1*3⁰
caba   : 3*3³ + 1*3² + 2*3¹ + 1*3⁰

abacaba: 1*3⁶ + 2*3⁵ + 1*3⁴     +     3*3³ + 1*3² + 2*3¹ + 1*3⁰
		 ==================
		 Essa parte é a hash de aba * 3^(size[abac])
=> inv [abacaba] = inv[aba]*pot[size[abac]] + inv[abac]

OBS: inv[primeira+segunda] != normal[segunda+primeira]
	 inv[abac+aba]         != normal[aba+abac] 
*/


int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	pot[0] = 1;
	for(int i = 1; i<520; i++)
		pot[i] = mul(pot[i-1], A);
	int t, n;
	cin >> t;
	string s;
	
	int caso=1;
	while (t--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> s;
			normal[i] = getHash(s, false);
			inv[i] = getHash(s, true);
			sz[i] = (int)s.size();
		}
		
		ll N = 0LL;
		ll I = 0LL;
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if(i==j) continue;
				N = (mul(normal[i], pot[sz[j]]) + normal[j])%MOD;
				I = (mul(inv[j]   , pot[sz[i]]) + inv[i])%MOD;
				ans += N==I;
			}
		}
		cout << "Case #" << caso++ << ": " << ans << "\n";
		
	}
	
	
	
	
	
	
	return 0;
}
