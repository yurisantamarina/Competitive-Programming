#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long int ll;
#define MAXN 200010
#define pb push_back
#define F first
#define S second
#define mp make_pair
ll inf = 1000000000000LL;

//~ Só funciona a segtree pois a recorrencia é dp[i] = max(cost(j, i)), se fosse algo do tipo dp[i] = max(dp[j] + cost(j, i)) não daria pra botar tudo em um vetor e criar a segtree por cima, pois eu dependo de estados anteriores, nesse caso só dependo do cost(j, i), que eu consigo calcular em O(1). Entao eu preciso, para cada i, achar um j que faz o cost(j, i) ser máximo.

struct reta{
	ll a, b;
	reta(){}
	reta(ll _a, ll _b){
		a = _a;
		b = _b;
	}
	
	ll getVal(ll x){
		return a*x+b;
	}
};

struct cht{
	vector<reta> ch;
	int sz;
	cht(){
		sz = 0;
	}
	
	bool pode(reta ant, reta top, reta at){
		return (ant.b-at.b)*(top.a-ant.a) <= (ant.b-top.b)*(at.a-ant.a);
	}
	
	void add(reta r){
		//~ printf("inserindo y = %lldx + %lld\n", r.a, r.b);
		while (sz > 1 && pode(ch[sz-2], ch[sz-1], r))
		{
			sz--;
			ch.pop_back();
		}
		sz++;
		ch.pb(r);
	}
	
	ll query(ll x){
		int lo = 0, hi = sz-1, mid, ans=0;
		while (lo <= hi)
		{
			mid = (lo+hi)/2;
			if(mid+1 == sz) return ch[mid].getVal(x);
			if(ch[mid].getVal(x) < ch[mid+1].getVal(x)){
				lo = mid+1;
			}else{
				hi = mid-1;
				ans = mid;
			}
		}
		
		return ch[ans].getVal(x);
	}
};

ll v[MAXN], n;
ll dp[MAXN];
ll prod[MAXN];
ll sum[MAXN];

void build(){
	sum[0] = 0LL;
	prod[0] = 0LL;
	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i-1] + v[i];
		prod[i] = prod[i-1] + v[i]*ll(i);
	}
}
reta vet[MAXN];
cht st[4*MAXN];

void build(int no, int l, int r){
	if(l==r){
		st[no] = cht();
		st[no].add(vet[l]);
		return;
	}
	int nxt=2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	int i = 0, j = 0;
	
	st[no] = cht();
	while (i < st[nxt].sz || j < st[nxt+1].sz)
	{
		if(i == st[nxt].sz){
			st[no].add(st[nxt+1].ch[j++]);
		}else if(j == st[nxt].sz){
			st[no].add(st[nxt].ch[i++]);
		}else{
			if(st[nxt].ch[i].a < st[nxt+1].ch[j].a){
				st[no].add(st[nxt].ch[i++]);
			}else{
				st[no].add(st[nxt+1].ch[j++]);
			}
		}
	}
	
}

ll query(int no, int l, int r, int i, int j, ll x){
	if(r < i || l > j) return 0LL;
	if(i<=l && r<=j) return st[no].query(x);
	int nxt = 2*no, mid = (l+r)/2;
	
	return max(query(nxt, l, mid, i, j, x), query(nxt+1, mid+1, r, i, j, x));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
	}
	
	build();
	
	for (int i = 1; i <= n; i++)
	{
		vet[i-1] = reta((i-1), sum[i-1]*(i-1) - prod[i-1]);
	}
	build(1, 0, n-1);
	
	dp[0] = 0LL;
	
	cht CH;
	//~ cout << "oi\n";
	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		dp[i] = query(1, 0, n-1, 0, i-1, -sum[i]) + prod[i];
		ans = max(ans, dp[i]);
		
		//~ cout << "dp[" << i << "] = " << dp[i] << endl;
	}
	cout << ans << "\n";
	
	
	
	return 0;
}
 
