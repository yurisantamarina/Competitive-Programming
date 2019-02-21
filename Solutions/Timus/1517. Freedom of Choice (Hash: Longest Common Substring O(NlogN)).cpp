#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 100100
const ll A = 33;//ou 1009
const ll MOD = 9LL + 1e18;

ll pot[MAXN];

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

int le, ri;
string a, b;

bool ok(int tam){
	
	ll hashA=0LL;
	ll hashB=0LL;
	//~ cout << "\nchute = " << tam << endl;
	unordered_map<ll, char> mapa;
	for (int i = 0; i < tam; i++)
		hashA = add(hashA, a[i]-'A');
	mapa[hashA];
	//~ cout << "hashA = " << hashA << endl;
	//~ cout << "Substrings de A:\n";
	//~ cout << a.substr(0, tam) << " " << hashA << endl;
	
	for (int i = tam; i < a.size(); i++)
	{
		hashA -= mul(pot[tam-1], a[i-tam]-'A');
		hashA = add(hashA, a[i]-'A');
		mapa[hashA];
		//~ cout << a.substr(i-tam+1, tam) << " " << hashA << endl;
	}
	
	for (int i = 0; i < tam; i++)
		hashB = add(hashB, b[i]-'A');
		
	//~ cout << "Substrings de B:\n";
	//~ cout << b.substr(0, tam) << " " << hashB << endl;
	
	if(mapa.find(hashB)!=mapa.end()){
		le = 0;
		ri = tam-1;
		return true;
	}
	
	for (int i = tam; i < b.size(); i++)
	{
		hashB -= mul(pot[tam-1], b[i-tam]-'A');
		hashB = add(hashB, b[i]-'A');
		if(mapa.find(hashB)!=mapa.end()){
			le = i-tam+1;
			ri = i;
			return true;
		}
		//~ cout << b.substr(i-tam+1, tam) << " " << hashB << endl;
	}
	
	//~ cout << "FALSE\n";
	return false;
}

int main () {
	
	int n;
	pot[0] = 1LL;
	for (int i = 1; i < MAXN; i++)
	{
		pot[i] = mul(pot[i-1], A);
	}
	
	
	cin >> n;
	cin >> a >> b;
	
	int lo = 1;
	int hi = n;
	int mid;
	
	int ans;
	int l, r;
	for (int k = 0; k < 32; k++)
	{
		mid = (lo+hi)/2;
		if(ok(mid)){
			lo = mid;
			ans = mid;
			l = le;
			r = ri;
		}else{
			hi = mid;
		}
	}
	if(ok(hi) && hi > ans){
		ans = hi;
		l = le;
		r = ri;
	}
	//~ cout << ans << " " << b.substr(l, r-l+1) << "\n";
	cout << b.substr(l, ans) << "\n";
	
	
	
	
	
	
	return 0;
}
