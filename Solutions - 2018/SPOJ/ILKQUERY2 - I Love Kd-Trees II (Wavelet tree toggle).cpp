#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back

struct BIT{
	vector<int> bit;
	int n;
	BIT(){
		bit.clear();
		n = 0;
	}
	BIT(int sz){
		n = sz;
		bit.resize(n, 0);
		for (int i = 1; i <= sz; i++)
			update(i, 1);
	}
	
	void update(int pos, int val){
		for(int i = pos; i < n; i += i & -i)
			bit[i] += val;
	}
	
	int sum(int pos){
		int ans = 0;
		for(int i = pos; i > 0; i -= i & -i)
			ans += bit[i];
		return ans;
	}
	
	int query(int l, int r){
		if(l > r) return 0;
		return sum(r) - sum(l-1);
	}
};

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	BIT bit;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn; hi = mx;
		if(from == to) return;
		
		bit = BIT(to - from + 2);
		if(mn == mx) return;
		
		int mid = (lo+hi)/2;
		auto f = [mid](int i){return i <= mid;};
		
		b.pb(0);
		for(int *i = from; i != to; i++)
			b.pb(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int esq(int i){
		return b[i] == b[i-1] + 1;
	}
	
	void toggle(int pos, int val){
		bit.update(pos, val);
		if(lo == hi) return;
		if(esq(pos)) left->toggle(b[pos], val);
		else right->toggle(pos - b[pos], val);
	}
	
	int rank(int l, int r, int k){
		if(hi < k || lo > k || l > r) return 0;
		if(lo == hi) return bit.query(l, r);
		return left->rank(b[l-1] + 1, b[r], k) + right->rank((l-1) - b[l-1] + 1, r - b[r], k);
	}
};

char ativo[MAXN];
int v[MAXN], cp[MAXN];

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
		ativo[i] = 1;
		cp[i] = v[i];
	}
	sort(cp + 1, cp + n + 1);
	for(int i = 1; i <= n; i++)
		v[i] = lower_bound(cp + 1, cp + n + 1, v[i]) - cp;
	
	wavelet *root = new wavelet(v + 1, v + n + 1, 1, n);
	
	int op, c, l, r, k;
	while (q--)
	{
		scanf("%d", &op);
		if(op == 0){
			scanf("%d %d %d", &l, &r, &k);
			l++; r++;
			if(!binary_search(cp + 1, cp + n + 1, k)) printf("0\n");
			else{
				k = lower_bound(cp + 1, cp + n + 1, k) - cp;
				printf("%d\n", root->rank(l, r, k));
			}
		}else{
			scanf("%d", &l);
			l++;
			if(ativo[l]){
				c = -1;
				ativo[l] = 0;
			}else{
				c = 1;
				ativo[l] = 1;
			}
			root->toggle(l, c);
		}
	}
	
	
	
	return 0;
}
