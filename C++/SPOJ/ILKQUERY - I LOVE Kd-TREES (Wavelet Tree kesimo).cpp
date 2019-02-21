#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN 101010

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn;
		hi = mx;
		if(from == to || mn == mx) return;
		int mid = (lo+hi)/2;
		auto f = [mid](int i){return i <= mid;};

		b.pb(0);
		for (int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int kth(int l, int r, int k){
		if(lo == hi) return lo;
		int inLeft = b[r] - b[l-1];
		
		if(inLeft >= k) return left->kth(b[l-1] + 1, b[r], k);
		return right->kth((l-1) - b[l-1] + 1, r - b[r], k - inLeft);
	}
};

int rev[MAXN], n, q, v[MAXN], cp[MAXN];
vector<int> pos[MAXN];

int main(){
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &v[i]);
		cp[i] = v[i];
	}
	
	int m;
	sort(cp + 1, cp + n + 1);
	for (int i = 1; i <= n; i++)
	{
		m = lower_bound(cp + 1, cp + n + 1, v[i]) - cp - 1;
		v[i] = m;
		rev[m] = v[i];
		pos[v[i]].pb(i-1);
	}
	
	wavelet *root = new wavelet(v + 1, v + n + 1, 0, n+1);
	
	int k, i, l, kth, ans;
	while (q--)
	{
		scanf("%d %d %d", &k, &i, &l);
		kth = root->kth(1, i+1, k);
		if(pos[kth].size() < l) ans = -1;
		else ans = pos[kth][l-1];
		printf("%d\n", ans);
	}
	
	
	
	return 0;
}
