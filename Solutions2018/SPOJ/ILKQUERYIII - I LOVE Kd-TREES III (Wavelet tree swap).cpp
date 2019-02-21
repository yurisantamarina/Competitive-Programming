#include <bits/stdc++.h>
 
using namespace std;
#define pb push_back
#define MAXN 1001010
#define all(v) v.begin(), v.end()
 
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
	
	bool esq(int i){return b[i] == b[i-1] + 1;}
	bool dir(int i){return !esq(i);}
	
	void update(int i){
		if(lo == hi) return;
		if(esq(i) && dir(i+1)) b[i]--;
		else if(dir(i) && esq(i+1)) b[i]++;
		else if(esq(i)) left->update(b[i]);
		else right->update(i - b[i]);
	}
};
 
wavelet *root;
vector<int> pos[MAXN];
int v[MAXN], cp[MAXN], mp[MAXN], n;
 
int query(int i, int l, int k){
	int d = root->kth(1, i+1, k);
	if(pos[d].size() < l) return -1;
	return pos[d][l-1] - 1;
}
 
void update(int i){
	if(i == n || cp[i] == cp[i+1]) return;
	
	int at = lower_bound(all(pos[cp[i]]), i) - pos[cp[i]].begin();
	pos[cp[i]][at]++;
	
	at = lower_bound(all(pos[cp[i+1]]), i+1) - pos[cp[i+1]].begin();
	pos[cp[i+1]][at]--;
	root->update(i);
	swap(cp[i], cp[i+1]);
}
 
int main(){
	int q, op;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
		mp[i] = v[i];
	}
	sort(mp + 1, mp + n + 1);
	for (int i = 1; i <= n; i++)
	{
		//~ printf("v = %d\n", v[i]);
		v[i] = lower_bound(mp + 1, mp + n + 1, v[i]) - mp;
		pos[v[i]].pb(i);
		cp[i] = v[i];
	}
	
	
	root = new wavelet(v + 1, v + n + 1, 1, n+1);
	while (q--)
	{
		scanf("%d", &op);
		int i, l, k;
		if(op == 0){
			scanf("%d %d %d", &i, &l, &k);
			printf("%d\n", query(i, l, k));
		}else{
			scanf("%d", &i);
			i++;
			//~ printf("atualizado i = %d cp[i] = %d  cp[i+1] = %d\n", i, cp[i], cp[i+1]);
			update(i);
		}
	}
	
	return 0;
}
