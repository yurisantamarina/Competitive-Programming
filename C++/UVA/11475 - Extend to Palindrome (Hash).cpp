#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 100010

const ll A = 33;//ou 3 ou 1009
const ll MOD = 9LL + 1e18;

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

ll hashP[MAXN];
ll hashS[MAXN];
ll pot[MAXN];
string s;

ll getP(int l, int r){
	return (hashP[r+1]+MOD - mul(hashP[l], pot[r-l+1]))%MOD;
}

ll getS(int L, int R){
	int l = s.size() - R - 1;
	int r = s.size() - L - 1;
	return (hashS[r+1]+MOD - mul(hashS[l], pot[r-l+1]))%MOD;
}

bool palindromo(int l, int r){
	return getP(l, r) == getS(l, r);
}

void build(){
	hashP[0] = 0LL;
	for (int i = 1; i <= s.size(); i++)
		hashP[i] = add(hashP[i-1], s[i-1]-'a'+1);
	
	hashS[0] = 0LL;
	for (int j = 1, i = s.size()-1; j <= s.size(); j++, i--)
	{
		hashS[j] = add(hashS[j-1], s[i]-'a'+1);
	}
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	for (int i = 0; i < MAXN; i++)
		pot[i] = i ? mul(pot[i-1], A) : 1LL;
	
	
	
	while (cin >> s)
	{
		build();
		if(palindromo(0, s.size()-1)){
			cout << s << "\n";
			continue;
		}
		
		ll fst, snd, totalP, totalS;
		string aux, aux2;
		for(int i = 0; i < s.size(); i++){
			fst = getS(0, i);
			snd = getP(0, s.size()-1); snd = mul(snd, pot[i+1]);
			totalP = (snd+fst)%MOD;
			
			//~ cout << s << " " << aux << endl;
			
			fst = getP(0, i); 
			//~ if(!i) cout << "fst = " << fst << "\n";
			fst = mul(fst, pot[s.size()]);
			//~ if(!i) cout << "fst = " << fst << "\n";
			snd = getS(0, s.size()-1);
			//~ if(!i) cout << "snd = " << snd << "\n";
			totalS = (fst+snd)%MOD;
			
			if(totalP == totalS){
				aux = s.substr(0, i+1);
				reverse(aux.begin(), aux.end());
				cout << s << aux << "\n";
				break;
			}
		}
	}
	
	
	return 0;
}
