#include <bits/stdc++.h>

using namespace std;
#define MAXN 100010
#define pb push_back
typedef long long int ll;

int v[MAXN];
struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int from, int to, int mn, int mx){
		lo = mn;
		hi = mx;
		if(from == to || mn == mx) return;
		
		int mid = (lo + hi) / 2;
		auto func = [mid](int i){
			return i <= mid;
		};
		
		b.pb(0);
		for(int i = from; i < to; i++)
			b.pb(b.back() + func(v[i]));
		
		int pivo = stable_partition(v + from, v + to, func) - (v);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int kth(int l, int r, int k){
		if(lo == hi) return lo;
		int c = b[r] - b[l-1];
		if(c >= k) return left->kth(b[l-1] + 1, b[r], k);
		return right->kth((l-1) - b[l-1] + 1, r - b[r], k - c);
	}
};

int main(){
	int n, q, l, r, k;
	map<int, int> rev;
	vector<int> cp;
	
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
		cp.pb(v[i]);
	}
	sort(cp.begin(), cp.end());
	int m;
	for (int i = 1; i <= n; i++)
	{
		m = lower_bound(cp.begin(), cp.end(), v[i]) - cp.begin();
		rev[m] = v[i];
		v[i] = m;
	}
	
	
	wavelet *root = new wavelet(1, n + 1, 0, n);
	while (q--)
	{
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", rev[root->kth(l, r, k)]);
	}
	
	
	return 0;
}	
