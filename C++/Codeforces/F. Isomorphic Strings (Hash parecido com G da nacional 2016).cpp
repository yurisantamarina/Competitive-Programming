#include <bits/stdc++.h>

using namespace std;


#define MAXN 200100
#define pb push_back
typedef long long int ll;
const ll A = 1009;
const ll MOD = 9LL + 1e18;
ll pot[MAXN];
map<char, int> mapa;

ll normalize(ll r){
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll mul(ll a, ll b){
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
	vector<int> s;
	ll a[MAXN];
	
	Hash(){}
	Hash(vector<int> vv){
		s = vv;
	}
	
	void build(){
		a[0] = 0LL;
		for (int i = 1; i <= (int)s.size(); i++){
			a[i] = add(a[i-1], s[i-1]);
		}
	}
	
	ll get(int l, int r){
		if(l>r) return 0LL;
		ll ans = (a[r+1] - mul(a[l], pot[r-l+1]))%MOD;
		return normalize(ans);
	}
};

vector<int> occ[29];

int get(int id, int val){
	//~ return 0;
	int pos = lower_bound(occ[id].begin(), occ[id].end(), val) - occ[id].begin();
	if(pos == occ[id].size()) return 100000000;
	return occ[id][pos];
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	buildPot();
	
	int n, q;
	string s;
	cin >> n >> q;
	cin >> s;
	vector<int> v;
	for (int i = 0; i < s.size(); i++)
	{
		if(!mapa.count(s[i])) v.pb(-1+2);
		else v.pb(i - mapa[s[i]] + 2);
		mapa[s[i]] = i;
		occ[s[i]-'a'].pb(i);
		//~ cout << v[i] << " ";
	}
	//~ cout << endl;
	Hash H = Hash(v);
	H.build();
	
	int l1, l2, len, r1, r2, pos;
	ll h1, h2;
	int cnt = 0;
	while (q--)
	{
		cin >> l1 >> l2 >> len;
		r1 = l1+len-1;
		r2 = l2+len-1;
		l1--;
		l2--;
		r1--;
		r2--;
		
		h1 = H.get(l1, r1);
		h2 = H.get(l2, r2);
		
		//~ cout << "h1 = " << h1 << endl;
		//~ printf("query %d\n", cnt++);
		//~ printf("l1 = %d  r1 = %d   l2 = %d  r2 = %d\n", l1, r1, l2, r2);
		for (int i = 0; i < 26; i++)
		{
			pos = get(i, l1);
			if(pos > r1) continue;
			
			//~ printf("tirando da posicao %d na string 1  v[%d] = %d  pot[%d]\n", pos, pos, v[pos], r1-pos-1);
			h1 -= mul(v[pos], pot[r1-pos]);
			h1 = normalize(h1);
			
			h1 += mul(1, pot[r1-pos]);
			h1 = normalize(h1);
		}
		
		//~ cout << "h1 = " << h1 << endl;
		
		for (int i = 0; i < 26; i++)
		{
			pos = get(i, l2);
			if(pos > r2) continue;
			
			h2 -= mul(v[pos], pot[r2-pos]);
			h2 = normalize(h2);
		
			h2 += mul(1, pot[r2-pos]);
			h2 = normalize(h2);
		}
		
		if(h1 == h2) cout << "YES\n";
		else cout << "NO\n";
		
		
	}
	
	
	return 0;
}
