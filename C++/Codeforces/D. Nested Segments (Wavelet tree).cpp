#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define F first
#define S second
#define pb push_back

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn; hi = mx;
		if(from == to) return;
		if(mn == mx) return;
		int mid = (lo + hi) / 2;
		auto f = [mid](int i){return i <= mid;};
		b.pb(0);
		for(int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid + 1, mx);
	}
	
	int query(int l, int r, int k){
		if(l > r) return 0;
		if(hi < k) return r - l + 1;
		if(lo >= k) return 0;
		
		return left->query(b[l-1] + 1, b[r], k) + right->query((l - 1) - b[l-1] + 1, r - b[r], k);
	}
};

int v[MAXN], ans[MAXN];
vector<pair<int, pair<int, int> > > vet;
vector<int> mapa;

int main(){
	int n, l, r;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &l, &r);
		vet.pb({l, {r, i}});
		mapa.pb(r);
	}
	sort(mapa.begin(), mapa.end());
	sort(vet.begin(), vet.end());
	for (int i = 1; i <= n; i++)
		v[i] = lower_bound(mapa.begin(), mapa.end(), vet[i-1].S.F) - mapa.begin();
	
	wavelet *root = new wavelet(v + 1, v + n + 1, 0, n + 1);
	
	for (int i = 1; i <= n; i++){
		ans[vet[i-1].S.S] = root->query(i + 1, n, lower_bound(mapa.begin(), mapa.end(), vet[i-1].S.F) - mapa.begin());
	}
	
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	
	
	return 0;
}
