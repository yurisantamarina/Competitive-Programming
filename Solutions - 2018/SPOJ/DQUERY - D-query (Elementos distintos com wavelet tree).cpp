#include <bits/stdc++.h>

using namespace std;

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn; hi = mx;
		if(from == to || mn == mx) return;
		int mid = (lo + hi) / 2;
		auto f = [mid](int i){ return i <= mid; };
		b.push_back(0);
		for(int *i = from; i != to; i++)
			b.push_back(b.back() + f(*i));
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	int query(int l, int r, int k){
		if(l > r || k <= lo) return 0;
		if(hi < k) return r - l + 1;
		return left->query(b[l-1] + 1, b[r], k) + right->query((l-1) - b[l-1] + 1, r - b[r], k);
	}
};

int lst[1010101];
int v[101010], n, q, l, r, x;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &x);
		if(lst[x] == 0) v[i] = 0;
		else v[i] = lst[x];
		lst[x] = i;
	}
	wavelet *root = new wavelet(v + 1, v + n + 1, 0, 1000010);
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		scanf("%d %d", &l, &r);
		printf("%d\n", root->query(l, r, l));
	}
	
	
	return 0;
}
