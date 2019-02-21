#include <bits/stdc++.h>

using namespace std;
#define LOG 20
#define F first
#define S second
#define MAXN 300010
#define mp make_pair
typedef pair<int, int> pii;

int n;
pii st[MAXN][LOG];
int v[MAXN];

pii merge(pii a, pii b){
	return mp(min(a.F, b.F), __gcd(a.S, b.S));
}

void build(){
	for (int i = 0; i < n; i++)
		st[i][0] = mp(v[i], v[i]);

	for (int j = 1; j < LOG; j++)
		for (int i = 0; i + (1<<j) - 1 < n; i++)
			st[i][j] = merge(st[i][j-1], st[i + (1<<(j-1))][j-1]);
}

pii query(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
	return merge(st[l][k], st[r - (1<<k) + 1][k]);
}

bool ok(int tam){
	int l = 0, r = tam-1;
	pii aux;
	while (r < n)
	{
		aux = query(l, r);
		if(aux.F == aux.S) return true;
		l++;
		r++;
	}
	return false;
}

int main (){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	build();
	
	int lo = 1, hi = n, mid;
	int ans = 0;
	
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(ok(mid)){
			ans = max(ans, mid);
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	
	vector<int> saida;
	int l = 0, r = ans-1;
	pii aux;
	
	while (r < n)
	{
		aux = query(l, r);
		if(aux.F == aux.S) saida.push_back(l+1);
		l++;
		r++;
	}
	cout << (int)saida.size() << " " << ans-1 << "\n";
	for (int i = 0; i < (int)saida.size(); i++)
	{
		cout << saida[i] << " ";
	}
	cout << "\n";
	
	
	
	
	
	
	return 0;
}
