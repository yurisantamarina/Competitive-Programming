#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define S second
#define F first
typedef long long int ll;

struct pv{
	ll x, y;
	pv(){}
	pv(ll _x, ll _y){
		x = _x;
		y = _y;
	}
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	int getQuad(){
		if(x>=0 && y>=0) return 1;
		if(x < 0 && y>=0) return 2;
		if(x <= 0 && y<0) return 3;
		return 4;
	}
};

ll cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

bool compare(pv a, pv b){
	int q1 = a.getQuad();
	int q2 = b.getQuad();
	
	if(q1 == q2){
		return cross(a, b) > 0LL;
	}
	return q1 < q2;
}

vector<pv> pts, cp;
unordered_map<ll, int> dist;
ll calc(pv a, pv b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

int n;

int solve(int idx){
	cp.clear();
	dist.clear();
	for (int i = 0; i < n; i++)
	{
		if(i==idx) continue;
		
		dist[calc(pts[i], pts[idx])]++;
	}
	
	int ans = 0;
	for (auto i : dist)
	{
		ans += (i.S*(i.S-1))/2;
	}
	
	return ans;
}

int main(){
	ll x, y;
	while (cin >> n, n)
	{
		pts.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			pts.pb(pv(x, y));
		}
		
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			ans += solve(i);
		}
		cout << ans << "\n";
	}
	
	
	return 0;
}
