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
const ll MOD = 1000000007LL;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 1000000

unordered_set<ll> s;
vector<ll> v;

void crivo(){
	bitset<MAXN> bs;
	bs.set();
	for (ll i = 2; i < MAXN; i++)
	{
		if(bs[i]){
			for (ll j = i*i; j < MAXN; j += i)
			{
				bs[j] = false;
			}
			
			for (ll j = i*i; j < MAXN*1LL*MAXN; j *= i)
			{
				if(s.count(j)==0){
					v.pb(j);
					//~ if(j==36) cout << i << endl;
					s.insert(j);
				}
			}			
		}
	}
	sort(v.begin(), v.end());
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	crivo();
	//~ for (int i = 0; i < 20; i++)
	//~ {
		//~ cout << v[i] << " ";
	//~ }
	//~ cout << endl;
	int tc;
	cin >> tc;
	ll l, r;
	for (int i = 0; i < tc; i++)
	{
		cin >> l >> r;
		l = lower_bound(v.begin(), v.end(), l) - v.begin();
		r = upper_bound(v.begin(), v.end(), r) - v.begin();
		cout << r-l << "\n";
	}
	
	
	return 0;
}
