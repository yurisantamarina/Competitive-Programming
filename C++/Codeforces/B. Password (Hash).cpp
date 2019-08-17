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
const int N = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

const ll A = 1009;
const ll MOD = 9LL + 1e18;

ll hashP[1000010];
ll pot[1000010];
string s;

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ll((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}


ll getP(int l, int r){
	ll ans = (hashP[r+1] - mul(hashP[l], pot[r-l+1]))%MOD;
	while(ans<0) ans+=MOD;
	while(ans>=MOD) ans-=MOD;
	return ans;
}

bool find(int tam){
	ll h = getP(0, tam-1);
	int l = 1;
	int r = tam;
	
	while (r < s.size()-1)
	{
		if(getP(l, r) == h) return true;
		
		l++;
		r++;
	}
	return false;
}

int main () {
	cin >> s;
	if(s.size()==1){
		cout << "Just a legend\n";
		return 0;
	}
	pot[0] = 1LL;
	for(int i = 1; i < 1000010; i++)
		pot[i] = mul(pot[i-1], A);
	
	hashP[0] = 0LL;
	for (int i = 1; i <= s.size(); i++)
		hashP[i] = add(hashP[i-1], s[i-1]-'a'+1);
	
	int ans = -1;
	for (int tam = s.size()-2; tam >= 1; tam--)
	{
		if(getP(0, tam-1) == getP(s.size()-tam, s.size()-1)){
			if(find(tam)){
				ans = tam-1;
				break;
			}
			//~ cout << s.substr(0, tam) << endl;
		}
	}
	
	if(ans!=-1) cout << s.substr(0, ans+1) << "\n";
	else cout << "Just a legend\n";
		
	return 0;
}
