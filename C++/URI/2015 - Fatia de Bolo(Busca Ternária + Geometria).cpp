#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
const ll MOD = 0;
const ll N = 0;

struct pv{
	ll x, y;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
};

int n;
ll total;
ll sum[100010];
vector<pv> ponto;

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

int add(int idx, int gap){
	idx += gap;
	idx %= n;
	if(idx==0) idx = n;
	return idx;
}

ll getArea(int u, int v){
	ll area1, area2;
	if(u > v) swap(u, v);
	
	if(u==1){
		area1 = sum[v-2];
		return area1;
	}
	
	area1 = sum[u-2] + (sum[n-2] - sum[v-2]) + abs(cross(ponto[u]-ponto[1], ponto[v]-ponto[1]));
	return area1;
}

int getAns(int idx){
	if(n==4){
		return add(idx, 2);
	}
	
	int lo = 2, hi = n-2;
	int mid1, mid2;
	
	ll area1, area2;
	ll dif1, dif2;
	ll best = LLONG_MAX;
	int v;
	for (int i = 0; i < 17; i++)
	{
		mid1 = (lo+hi)/2;
		mid2 = mid1+1;
		
		area1 = getArea(idx, add(idx, mid1));
		area2 = getArea(idx, add(idx, mid2));
		dif1 = abs((total - area1)- area1);
		dif2 = abs((total - area2)- area2);
		
		if(dif1 < dif2){
			if(dif1 < best){
				best = dif1;
				v = add(idx, mid1);
			}
			hi = mid2;
		}else{
			if(dif2 < best){
				best = dif2;
				v = add(idx, mid2);
			}
			lo = mid1;
		}
	}
	mid1 = lo;
	mid2 = hi;
	area1 = getArea(idx, add(idx, mid1));
	area2 = getArea(idx, add(idx, mid2));
	dif1 = abs((total - area1)- area1);
	dif2 = abs((total - area2)- area2);
	
	if(dif1 < dif2){
		if(dif1 < best){
			best = dif1;
			v = add(idx, mid1);
		}
		hi = mid2;
	}else{
		if(dif2 < best){
			best = dif2;
			v = add(idx, mid2);
		}
		lo = mid1;
	}
	return v;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n;
	ll x, y;
	
	ponto.pb(pv(0, 0));//lixo
	
	
	for (int i = 1; i <= n; i++)
	{
		cin >> x >> y;
		ponto.pb(pv(x, y));
	}
	
	sum[0] = 0LL;
	
	for (int i = 2; i < n; i++)
	{
		sum[i-1] = sum[i-2] + abs(cross(ponto[i] - ponto[1], ponto[i+1] - ponto[1]));
	}
	total = sum[n-2];
	
	int v;
	
	ll area1, area2;
	ll ans1, ans2;
	ll best = -1;
	
	for (int i = 1; i <= n; i++)
	{
		v = getAns(i);
		
		area1 = getArea(i, v);
		area2 = total - area1;
		if(abs(area1 - area2) > best){
			best = abs(area1 - area2);
			ans1 = max(area1, area2);
			ans2 = min(area1, area2);
		}
	}
	cout << ans1 << " " << ans2 << "\n";
	
	
	
	return 0;
}
