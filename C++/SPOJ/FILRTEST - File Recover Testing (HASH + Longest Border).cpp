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
#define MAXN 1000100
const ll A = 3;
const ll MOD = 9LL + 1e18;

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

ll pot[MAXN];
ll h[MAXN];

void build(string s){
	h[0] = 0LL;
	for (int i = 1; i <= s.size(); i++)
	{
		h[i] = add(h[i-1], s[i-1]-'a'+1);
	}
	
}

ll getHash(int l, int r){
	ll ans = (h[r+1] - mul(h[l], pot[r-l+1]));
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	pot[0] = 1LL;
	for (int i = 1; i < MAXN; i++)
	{
		pot[i] = mul(pot[i-1], A);
	}
	
	
	int L;
	string s;
	while (cin >> L >> s)
	{
		if(L==-1 && s=="*") break;
		build(s);
		ll h1, h2;
		int border = 0;
		for (int tam = 1; tam < s.size(); tam++)
		{
			h1 = getHash(0, tam-1);
			h2 = getHash(s.size()-tam, s.size()-1);
			
			if(h1==h2) border = tam;
		}
		cout << max((L-border)/((int)s.size() - border), 0) << endl;
	}
	
	
	
	
	
	return 0;
}
