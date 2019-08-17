#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (ll)floor(1 + log10((double)a))
#define digitCount(a, b) (ll)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<int, int> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};
#define MAXN 200010
int tree[MAXN];
unordered_map<int, int> mapa;
unordered_map<int, int> f;
int cnt = 1;
int rev[MAXN];
int qtd=0;

int read(int idx)
{
	int ret =0;
	while(idx>0)
	{
		ret+=tree[idx];
		idx-=idx&(-idx);
	}
	return ret;
}

void update(int idx, int val)
{
	while(idx<MAXN)
	{
		tree[idx]+=val;
		idx+=idx&(-idx);
	}
}

void add(int n){
	n = mapa[n];
	if(f[n] == 0){
		update(n, 1);
		f[n]++;
		qtd++;
	}
}

void del(int n){
	n = mapa[n];
	if(f[n] > 0){
		update(n, -1);
		f[n]--;
		qtd--;
	}
}

int kth(int k){
	if(qtd<k) return INT_MAX;
	int lo = 0, hi = MAXN+1, mid, aux;
	while(lo + 1 < hi){
		mid = (lo + hi)/2;
		aux = read(mid);
		if(aux < k) lo = mid;
		else hi = mid;
	}
	return rev[lo+1];
}

int count(int x){
	x = mapa[x];
	x--;
	return read(x);
}

int main(){
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int q, n;
	char op;
	cin >> q;
	vector<int> v;
	vector<ii> v2;
	while (q--)
	{
		cin >> op >> n;
		v.pb(n);
		v2.pb(mp(op, n));
	}
	
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
	{
		if(mapa.find(v[i]) == mapa.end()){
			rev[cnt] = v[i];
			mapa[v[i]] = cnt++;
		}
	}
	
	for (int i = 0; i < v2.size(); i++)
	{
		op = v2[i].F; n = v2[i].S;
		if(op == 'I') add(n);
		else if(op == 'D') del(n);
		else if(op == 'K'){
			int ans = kth(n);
			if(ans==INT_MAX) cout << "invalid\n";
			else cout << ans << "\n";
		}
		else cout << count(n) << "\n";
	}
	
	
	
	return 0;
}
 
