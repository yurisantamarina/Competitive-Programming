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

int ult[27];
int v[500010];
vector<int> pos[27];
ll pot[500010];
int ap[27];

ll normalize(ll r){
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	memset(ap, 0, sizeof ap);
	memset(ult, -1, sizeof ult);
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++)
	{
		pos[s[i]-'a'].pb(i);
		
		if(ult[s[i]-'a'] == -1) v[i] = 1;
		else v[i] = i-ult[s[i]-'a']+1;
		ult[s[i]-'a'] = i;
	}
	
	pot[0] = 1LL;
	for (int i = 1; i <= s.size(); i++)
	{
		pot[i] = mul(pot[i-1], A);
	}
	
	memset(ult, -1, sizeof ult);
	int sz, x;
	cin >> sz;
	
	ll hashPattern = 0LL;
	for (int i = 0; i < sz; i++)
	{
		cin >> x;
		if(ult[x] == -1) hashPattern = add(hashPattern, 1);
		else hashPattern = add(hashPattern, i-ult[x]+1);
		ult[x] = i;
	}
	
	int l, r;
	ll hashW = 0LL;
	for (int i = 0; i < sz; i++)
	{
		hashW = add(hashW, v[i]);
	}
	l = 0;
	r = sz-1;
	
	int ans = 0;
	int idx;
	int aux;
	while (r < s.size())
	{
		if(hashW == hashPattern) ans++;
		l++;
		r++;
		if(r==s.size()) break;
		
		aux = s[l-1]-'a';
		hashW -= mul(v[l-1], pot[sz-1]);
		hashW = normalize(hashW);
		hashW = add(hashW, v[r]);
		
		//~ pos[aux].erase(pos[aux].begin());
		ap[aux]++;
		if(ap[aux] < pos[aux].size()){
			idx = pos[aux][ap[aux]];
			if(idx>=l && idx<=r){
				hashW -= mul(v[idx], pot[sz-(idx-l)-1]);
				hashW = normalize(hashW);
				hashW += mul(1, pot[sz-(idx-l)-1]);
				hashW = normalize(hashW);
			}
			v[idx] = 1;
		}
	}
	cout << ans << "\n";
	
	return 0;
}
