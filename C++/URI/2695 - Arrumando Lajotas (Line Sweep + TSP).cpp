#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN 15
#define INF 1000000000000LL
typedef long long int ll;

struct pv{
	ll x, y;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
	pv operator + (pv other) const{
		return pv(x + other.x, y + other.y);
	}
	ll operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	ll operator * (pv other) const{
		return x * other.x + y * other.y;
	}
};

struct polygon{
	vector<pv> l, r;
	ll w, mn, mx;
	polygon(){
		l.clear();
		r.clear();
		w = 0;
		mn = INF;
		mx = -INF;
	}
	void addL(pv a){
		l.pb(a);
	}
	void addR(pv a){
		r.pb(a);
	}
};

struct reta{
	pv p0, v;
	reta(){}
	reta(pv a, pv b){
		p0 = a;
		v = b;
	}
};

ll H, n;
double dist[MAXN][MAXN];
char memo[MAXN][1<<MAXN];
double dp[MAXN][1<<MAXN];
polygon poly[MAXN];
vector<pv> tmp;

void build(ll idx, ll mn, ll mx){
	for (ll i = 1; i < tmp.size(); i++)
	{
		poly[idx].addR(tmp[i]);
		if(tmp[i].y == H) break;
	}
	
	poly[idx].addL(tmp[0]);
	for (ll i = tmp.size()-1; i >= 0; i--)
	{
		poly[idx].addL(tmp[i]);
		if(tmp[i].y == H) break;
	}
	poly[idx].w = mx - mn;
	poly[idx].mn = mn;
	poly[idx].mx = mx;
}

double tsp(ll u, ll mask){
	if(mask == (1<<n) - 1) return 0.0;
	if(memo[u][mask]) return dp[u][mask];
	memo[u][mask] = 1;
	double ans = 1000000000000000.0;
	for (ll i = 0; i < n; i++)
	{
		if(mask & (1<<i)) continue;
		ans = min(ans, dist[u][i] + tsp(i, mask | (1<<i)));
	}
	return dp[u][mask] = ans;
}

double getX(reta r, reta s){
    pv v = r.v;
    pv u = s.v;
    
    pv p0 = r.p0;
    pv p1 = s.p0;
    
    double t = ((1.0)*(u.x * (p0.y - p1.y) + u.y * (p1.x - p0.x))) / (v ^ u);
    
    return p0.x + (v.x * t);
}

double getDist(ll idx1, ll idx2){
	vector<pv> l = poly[idx1].r;
	vector<pv> r = poly[idx2].l;
	for (ll i = 0; i < r.size(); i++)
		r[i] = r[i] + pv(INF, 0);
	
	//~ for (int i = 0; i < l.size(); i++)
	//~ {
		//~ cout << l[i].x << " " << l[i].y << endl;
	//~ }
	
	ll mn = abs(poly[idx1].mn);
	double d = 10000000000000000000.0;
	
	ll i = 0, j = 0;
	
	while (i < l.size() && j < r.size())
	{
		if(l[i].y == r[j].y){
			d = min(d, (double)r[j].x - l[i].x);
			i++;
			j++;
		}else if(l[i].y < r[j].y){
			d = min(d, (double)abs(getX(reta(l[i], pv(1, 0)), reta(r[j-1], r[j] - r[j-1])) - l[i].x));
			i++;
		}else{
			d = min(d, (double)abs(r[j].x - getX(reta(r[j], pv(-1, 0)), reta(l[i-1], l[i] - l[i-1]))));
			j++;
		}
	}
	
	//~ printf("d = %.5lf\n", d);
	double mx = poly[idx2].mx + INF - d + mn;
	//~ printf("mx = %lld + %lld - %.5lf + %lld\n", poly[idx2].mx, 3, d, mn);
	double dif = (mx - poly[idx1].w);
	//~ printf("%lld + %lld - %.5lf\n\n", poly[idx1].w, poly[idx2].w, mx);
	return dif;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll k, x, y;
	H = 0;
	cin >> n;
	
	ll mn, mx;
	for (ll i = 0; i < n; i++)
	{
		cin >> k;
		tmp.clear();
		mn = INF;
		mx = -INF;
		while (k--)
		{
			cin >> x >> y;
			H = max(H, y);
			tmp.pb(pv(x, y));
			mn = min(mn, x);
			mx = max(mx, x);
		}
		build(i, mn, mx);
	}
	
	for (ll i = 0; i < n; i++)
	{
		for (ll j = 0; j < n; j++)
		{
			if(i == j) continue;
			dist[i][j] = getDist(i, j);
		}
	}
	
	double ans = 1000000000000000000.0;
	for (ll i = 0; i < n; i++)
	{
		ans = min(ans, poly[i].w + tsp(i, 1<<i));
	}
	cout << fixed << setprecision(3) << ans << "\n";
	
	return 0;
}
