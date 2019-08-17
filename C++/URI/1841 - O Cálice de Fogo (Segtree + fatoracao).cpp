#include <bits/stdc++.h>

using namespace std;
#define MAXP 10000002
#define MAXN 701010
#define MOD 1000000007
typedef long long int ll;

char comp[MAXP];
int cnt = 1;
unordered_map<int, int> mapa, rev;
int st[4*MAXN];

void crivo(){
	for (int i = 2; i < MAXP; i++)
	{
		if(comp[i]) continue;
		mapa[i] = cnt++;
		rev[mapa[i]] = i;
		for(int j = 2; (ll)i*j < MAXP; j++)
			comp[i*j] = 1;
	}
}

void update(int no, int l, int r, int pos){
	if(pos < l || pos > r) return;
	if(pos == l && l == r){
		st[no]++;
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	update(nxt, l, mid, pos);
	update(nxt+1, mid+1, r, pos);
	
	st[no] = ((ll)st[nxt] * st[nxt+1])%MOD;
}

int query(int no, int l, int r, int i, int j){
	if(l > r || i > j) return 1LL;
	if(r < i || l > j){
		return 1;
	}
	if(i<=l && r<=j){
		return st[no];
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	
	
	
	ll a = query(nxt, l, mid, i, j);
	ll b = query(nxt+1, mid+1, r, i, j);
	return (a * b) % MOD;
}

void fatora(ll n){
	for (int i = 2; i < cnt && n > 1; i++)
	{
		while(n % i == 0){
			n /= i;
			//~ printf("%d x ", i);
			//~ printf("update em %d\n", i);
			update(1, 0, MAXN-1, mapa[i]);
		}
	}
	//~ cout << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n;
	for (int i = 0; i < 4*MAXN; i++)
		st[i] = 1;
	crivo();
	cin >> n;
	
	
	fatora(n);
	
	int p;
	while (cin >> p)
	{
		update(1, 0, MAXN-1, mapa[p]);
		//~ printf("query %d %d\n", 1, mapa[p]-1);
		cout << query(1, 0, MAXN-1, 1, mapa[p]-1) << "\n";
		
	
	}
	
	
	return 0;
}
