#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define MAXN 10100
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

Hash H;
unordered_set<ll> hashes;
unordered_map<ll, string> mapa;
string s, nw, s2;
bool dp[MAXN];
int lst[MAXN];

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	buildPot();//cuidado com o limite do MAXN
	int n, m;
	cin >> n;
	
	
	ll h;
	
	cin >> s;
	reverse(s.begin(), s.end());
	s = "#" + s;
	H = Hash(s);
	H.build();
	cin >> m;
	
	char c;
	for (int i = 0; i < m; i++)
	{
		cin >> s2;
		h = 0LL;
		nw = "";
		for (int i = 0; i < s2.size(); i++)
		{
			c = tolower(s2[i]);
			h = add(h, c-'a'+1);
			nw += c;
		}
		mapa[h] = s2;
		hashes.insert(h);
	}
	
	dp[0] = true;
	for (int i = 1; i <= n; i++)
	{
		dp[i] = false;
		for (int j = i, cnt = 0; cnt <= 1000 && j >= 1; j--, cnt++)
		{
			if(hashes.count(H.getRangeNormal(j, i))){
				dp[i] |= dp[j-1];
				if(dp[j-1] == true){
					lst[i] = j-1;
				}
			}
		}
	}
	
	int at = lst[n];
	cout << mapa[H.getRangeNormal(at+1, n)] << " ";
	while (at > 0)
	{
		cout << mapa[H.getRangeNormal(lst[at]+1, at)] << " ";
		at = lst[at];
	}
	cout << "\n";
	
	
	
	return 0;
}
