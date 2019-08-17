//~ A ideia e saber para um determinado intervalo quantas vezes cada potencia de 2 aparece para consguir atualizar a soma. O XOR vai tirar algumas dessas potencia e botar algumas outras
#include <bits/stdc++.h>

using namespace std;
#define MAXN 110101
#define INF 1000000000000000LL
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long long int ll;

struct node{
	ll sum, tam;
	ll f[25];
	ll lazy;
	node(){
		memset(f, 0, sizeof f);
		sum = 0;
		lazy = 0;
		tam = 0;
	}
};

ll n, v[MAXN];
node st[4*MAXN];

void merge(ll no, ll esq, ll dir){
	st[no] = node();
	st[no].sum = st[esq].sum + st[dir].sum;
	st[no].tam = st[esq].tam + st[dir].tam;
	for (ll i = 0; i < 25; i++)
	{
		st[no].f[i] = st[esq].f[i] + st[dir].f[i];
	}
}

void build(ll no, ll l, ll r){
	if(l==r){
		st[no] = node();
		for (ll i = v[l]; i > 0; i -= i & -i)
		{
			st[no].f[__builtin_ctz(i & -i)]++;
		}
		st[no].sum = v[l];
		st[no].lazy = 0;
		st[no].tam = 1;
		return;
	}
	ll mid = (l+r)/2, nxt = 2*no;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	merge(no, nxt, nxt+1);
}

void propagate(ll no, ll l, ll r){
	if(st[no].lazy == 0) return;
	
	ll tmp;
	ll idx;
	for (ll i = st[no].lazy; i > 0; i -= i & -i)
	{
		tmp = i & -i;
		idx = __builtin_ctz(tmp);
		st[no].sum -= tmp * st[no].f[idx];
		st[no].sum += tmp * (st[no].tam - st[no].f[idx]);
		st[no].f[idx] = st[no].tam - st[no].f[idx];
	}
	
	ll nxt = 2*no;
	if(l != r){
		st[nxt].lazy ^= st[no].lazy;
		st[nxt+1].lazy ^= st[no].lazy;
	}
	st[no].lazy = 0;
}

void update(ll no, ll l, ll r, ll i, ll j, ll x){
	propagate(no, l, r);
	if(i>r || j<l) return;
	if(i<=l && r<=j){
		st[no].lazy ^= x;
		propagate(no, l, r);
		return;
	}
	ll mid = (l+r)/2, nxt = 2*no;
	update(nxt, l, mid, i, j, x);
	update(nxt+1, mid+1, r, i, j, x);
	merge(no, nxt, nxt+1);
}

ll query(ll no, ll l, ll r, ll i, ll j){
	propagate(no, l, r);
	if(i>r || j<l) return 0LL;
	if(i<=l && r<=j) return st[no].sum;
	
	ll mid = (l+r)/2;
	ll nxt = 2*no;
	
	return query(nxt, l, mid, i, j) + query(nxt+1, mid+1, r, i, j);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll m, op, l, r, x;
	cin >> n;
	for (ll i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	
	build(1, 0, n-1);
	cin >> m;
	for (ll i = 0; i < m; i++)
	{
		cin >> op >> l >> r;
		l--; r--;
		if(op == 1){
			cout << query(1, 0, n-1, l, r) << "\n";
		}else{
			cin >> x;
			update(1, 0, n-1, l, r, x);
		}
	}
	
	return 0;
}
