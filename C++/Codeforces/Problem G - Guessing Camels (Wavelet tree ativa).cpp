//~ http://codeforces.com/gym/101485

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
typedef long long int ll;

struct BIT{
	int n;
	vector<int> bit;
	BIT(){}
	BIT(int sz){
		n = sz;
		bit.resize(sz, 0);
	}
	
	void update(int pos, int val){
		for(int i = pos; i < n; i += i & -i)
			bit[i] += val;
	}
	int sum(int pos){
		int ans = 0;
		for(int i = pos; i > 0 ; i -= i & -i)
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
	BIT bit;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn;
		hi = mx;
		if(from == to) return;
		bit = BIT(to - from + 3);
		if(mn == mx) return;
		int mid = (lo+hi)/2;
		
		auto f = [mid](int i){return i <= mid;};
		b.push_back(0);
		for(int *i = from; i != to; i++)
			b.push_back(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int query(int l, int r, int k){
		if(l > r || lo > k) return 0;
		if(hi <= k) return bit.query(l, r);
		
		return left->query(b[l-1] + 1, b[r], k) + right->query((l-1) - b[l-1] + 1, r - b[r], k);
	}
	
	bool esq(int x){
		return b[x] == b[x-1] + 1;
	}
	
	void update(int pos){
		bit.update(pos, 1);
		if(lo == hi) return;
		
		if(esq(pos)) left->update(b[pos]);
		else right->update(pos - b[pos]);
	}
};

int n, vet[4][MAXN], pos2[MAXN], pos3[MAXN], preto1[MAXN], verde1[MAXN], preto2[MAXN], verde2[MAXN];


int main(){
	//dados dois vetores a, b e uma posicao i, quantos j existem tal que j < i && a[j] < a[i] && b[j] < b[i];
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++)
		scanf("%d", &vet[1][i]);
	
	for (int i = 1; i <= n; i++){
		scanf("%d", &vet[2][i]);
		pos2[vet[2][i]] = i;
	}
	for (int i = 1; i <= n; i++){
		scanf("%d", &vet[3][i]);
		pos3[vet[3][i]] = i;
	}
	
	vector<pair<int, int> > aux;
	for (int i = 1; i <= n; i++)
	{
		preto1[i] = pos2[vet[1][i]];
		verde1[i] = pos3[vet[1][i]];
		aux.push_back(make_pair(preto1[i], verde1[i]));
	}
	
	sort(aux.begin(), aux.end());
	
	for (int i = 1; i <= n; i++)
	{
		preto2[i] = aux[i-1].first;
		verde2[i] = aux[i-1].second;
	}
	
	wavelet *root = new wavelet(verde2 + 1, verde2 + n + 1, 1, n);
	
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += root->query(1, preto1[i] - 1, verde1[i] - 1);
		root->update(preto1[i]);
	}
	
	printf("%lld\n", ans);
	
	return 0;
}
