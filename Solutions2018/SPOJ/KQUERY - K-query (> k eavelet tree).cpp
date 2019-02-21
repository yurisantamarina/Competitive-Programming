#include <bits/stdc++.h>
 
using namespace std;
#define MAXN 100010
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
		int mid = (lo+hi)/2;
		auto f = [mid](int i){return i <= mid;};
		b.pb(0);
		for(int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int greaterThan(int l, int r, int k){
		if(k <= lo) return r - l + 1;
		if(k > hi || l > r) return 0;
		
		return left->greaterThan(b[l-1] + 1, b[r], k) + right->greaterThan((l-1) - b[l-1] + 1, r - b[r], k);
	}
};
 
int v[MAXN], n, q, l, r, k, cp[MAXN];
 
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
		cp[i] = v[i];
	}
	sort(cp + 1, cp + n + 1);
	int mn = 10101010;
	int mx = -mn;
	for(int i = 1; i <= n; i++){
		v[i] = lower_bound(cp + 1, cp + n + 1, v[i]) - cp;
		mn = min(mn, v[i]);
		mx = max(mx, v[i]);
	}
	
	//~ printf("mn = %d  mx = %d\n", mn, mx);
	scanf("%d", &q);
	wavelet *root = new wavelet(v + 1, v + n + 1, mn, mx);
	while (q--)
	{
		scanf("%d %d %d", &l, &r, &k);
		k = upper_bound(cp + 1, cp + n + 1, k) - cp;
		
		//~ printf("k = %d\n", k);
		printf("%d\n", root->greaterThan(l, r, k));
	}
	
	
	
	return 0;
}	
