#include <bits/stdc++.h>
using namespace std;
#define MAXN 101010
#define mp make_pair
#define pb push_back
#define F first
#define S second
typedef long long int ll;

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn; hi = mx;
		if(from == to || mn == mx) return;
		int mid = (mn + mx) / 2;
		auto f = [mid](int i){return i <= mid;};
		
		b.pb(0);
		for(int *it = from; it != to; it++)
			b.pb(b.back() + f(*it));
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid + 1, mx);
	}
	
	//~ (lo, hi) (kl, kr)
	
	int query(int l, int r, int kl, int kr){
		if(l > r || lo > kr || hi < kl) return 0;
		if(kl <= lo && hi <= kr) return r - l + 1;
		
		//~ cout << "lo = " << lo << "  hi = " << hi << "  k = " << k << endl;
		return left->query(b[l-1] + 1, b[r], kl, kr) + right->query((l - 1) - b[l-1] + 1, r - b[r], kl, kr);
	}
};

int v[MAXN], vx[MAXN];

int main(){
	int n, A, X, Y;
	vector<pair<int, int> > points;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> A;
	for (int i = 1; i <= n; i++)
	{
		cin >> X >> Y;
		points.pb(mp(X, Y));
	}
	
	sort(points.begin(), points.end());
	for (int i = 0; i < n; i++){
		v[i+1] = points[i].S;
		vx[i+1] = points[i].F;
	}
	
	//~ for (int i = 1; i <= n; i++)
		//~ cout << v[i] << " ";
	//~ cout << endl;
	
	wavelet *root = new wavelet(v + 1, v + n + 1, 1, 1000000);
	
	int ans = 0;
	for (int y = 1; y <= 1000000; y++)
	{
		int x = A / y;
		x = min(x, 1000000);
		
		int l = 1;
		int r = upper_bound(vx + 1, vx + n + 1, x) - vx - 1;
		//~ printf("x = %d  y = %d\n", x, y);
		//~ printf("l = %d  r = %d\n\n", l, r);
		ans = max(ans, root->query(l, r, 1, y));
	}
	
	cout << ans << "\n";
	
	return 0;
}
