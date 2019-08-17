#include <bits/stdc++.h>
 
using namespace std;
#define MAXN 1000010
#define pb push_back
typedef long long int ll;

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn;
		hi = mx;
		if(from == to || mn == mx) return;
		int mid = (lo + hi) / 2;
		auto f = [mid](int i){return i <= mid;};
		b.pb(0);
		for(int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int lessThan(int l, int r, int k){
		if(hi < k) return r - l + 1;
		if(lo >= k || l > r) return 0;
		return left->lessThan(b[l-1] + 1, b[r], k) + right->lessThan((l-1) - b[l-1] + 1, r - b[r], k);
	}
};

map<int, int> mapa;
int n, v1[MAXN], v2[MAXN], a[MAXN];
 
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mapa[a[i]]++;
		v1[i] = mapa[a[i]];
	}
	mapa.clear();
	
	for (int i = n; i >= 1; i--)
	{
		mapa[a[i]]++;
		v2[i] = mapa[a[i]];
	}
	
	wavelet *root = new wavelet(v2 + 1, v2 + n + 1, 1, n);
	
	ll ans = 0LL;
	for (int i = 1; i <= n - 1; i++)
		ans += (ll)root->lessThan(i+1, n, v1[i]);
	printf("%lld\n", ans);
	
	return 0;
}	
