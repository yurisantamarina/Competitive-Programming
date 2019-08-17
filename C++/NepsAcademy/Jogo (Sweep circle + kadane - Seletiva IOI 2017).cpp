#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 5050
#define pb push_back
ll INF = 1000000000000000000LL;

struct pv{
	ll x, y;
	ll cost;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	pv(ll a, ll b, ll c){
		x = a;
		y = b;
		cost = c;
	}
	
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y, cost);
	}
	
	ll operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	
	ll norma() const{
		return x * x + y * y;
	}
	
	int quad(){
		if(x >= 0 && y >= 0) return 1;
		if(x < 0 && y >= 0) return 2;
		if(x <= 0 && y < 0) return 3;
		return 4;
	}
};

bool compare(pv a, pv b){
	int q1 = a.quad();
	int q2 = b.quad();
	if(q1 != q2) return q1 < q2;
	ll c = a ^ b;
	if(c != 0) return c > 0;
	return a.norma() < b.norma();
}

vector<pv> vet, v;
ll acc[MAXN], mn[MAXN], idx, n;

ll kadane(){
	ll ans = -INF;
	for (int i = 1; i < idx; i++)
	{
		acc[i] += acc[i-1];
		mn[i] = min(mn[i - 1], acc[i]);
		if(i <= 1) continue;
		ans = max(ans, acc[i] - mn[i - 2]);
	}
	return ans;
}

ll sweep(){
	sort(v.begin(), v.end(), compare);
	pv lst = pv(0, 0);
	ll ans = -INF;
	for (int i = 0; i < v.size(); i++)
	{
		ll c = v[i] ^ lst;
		if(c == 0 && v[i].quad() == lst.quad()){
			acc[idx++] = v[i].cost;
		}else{
			ans = max(ans, kadane());
			idx = 2;
			acc[idx++] = v[i].cost;
		}
		
		lst = v[i];
	}
	return max(ans, kadane());
}

ll solve(int p){
	pv pivo = vet[p];
	acc[0] = 0;
	mn[0] = 0;
	acc[1] = pivo.cost;
	idx = 2;
	
	v.clear();
	for (int i = 0; i < n; i++)
	{
		if(i == p) continue;
		v.pb(vet[i] - pivo);
	}
	
	return sweep();
}

int main(){
	scanf("%lld", &n);
	ll x, y, c;
	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld %lld", &x, &y, &c);
		vet.pb(pv(x, y, c));
	}
	
	ll ans = -INF;
	for (int i = 0; i < n; i++){
		ans = max(ans, solve(i));
	}
	
	printf("%lld\n", ans);
	return 0;
}
