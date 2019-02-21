#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000010
typedef long long int ll;

int bit[MAXN], pref[MAXN], suf[MAXN], v[MAXN], n;
unordered_map<int, int> mapa;

void update(int pos, int val){
	for(pos; pos < MAXN; pos += pos & -pos){
		bit[pos] += val;
	}
}

int query(int pos){
	int ans = 0;
	for(pos; pos > 0; pos -= pos & -pos){
		ans += bit[pos];
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &v[i]);
	}
	
	for (int i = 1; i <= n; i++)
	{
		mapa[v[i]]++;
		pref[i] = mapa[v[i]];
	}
	mapa.clear();
	for (int i = n; i >= 1; i--)
	{
		mapa[v[i]]++;
		suf[i] = mapa[v[i]];
		update(suf[i], 1);
	}
	
	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		update(suf[i], -1);
		ans += ll(query(pref[i]-1));
	}
	printf("%lld\n", ans);
	
	return 0;
}
