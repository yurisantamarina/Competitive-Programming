#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010

struct pv{
	int x, y;
};

pv v[MAXN];
pv a, b, t;
int n;
char memo[2][2][MAXN];
long double dp[2][2][MAXN];

long double dist(pv a, pv b){
	return hypot(a.x - b.x, a.y - b.y);
}

long double solve(int usouA, int usouB, int pos){
	if(pos == n) return usouA && usouB ? 0 : 10000000000000000000.0;
	if(memo[usouA][usouB][pos]) return dp[usouA][usouB][pos];
	memo[usouA][usouB][pos] = 1;
	
	long double ans = 10000000000000000000.0;

	if(usouA) ans = min(ans, dist(t, v[pos]) * 2 + solve(usouA, usouB, pos+1));
	else ans = min({ans, dist(t, v[pos])*2 + solve(usouA, usouB, pos+1), dist(a, v[pos]) + dist(v[pos], t) + solve(1, usouB, pos+1)});
	
	if(usouB) ans = min(ans, dist(t, v[pos]) * 2 + solve(usouA, usouB, pos+1));
	else ans = min({ans, dist(t, v[pos])*2 + solve(usouA, usouB, pos+1), dist(b, v[pos]) + dist(v[pos], t) + solve(usouA, 1, pos+1)});
	
	
	
	return dp[usouA][usouB][pos] = ans;
}

int main(){
	int ax, ay, bx, by, tx, ty;
	cin >> ax >> ay >> bx >> by >> tx >> ty;
	cin >> n;
	a.x = ax;
	a.y = ay;
	b.x = bx;
	b.y = by;
	t.x = tx;
	t.y = ty;
	
	long double totA = 0;
	
	for (int i = 0; i < n; i++){
		cin >> v[i].x >> v[i].y;
		totA += dist(t, v[i]) * 2;
	}
	
	
	long double ans = 10000000000000000000.0;
	
	for (int i = 0; i < n; i++)
	{
		long double tmp = totA;
		tmp -= dist(t, v[i])*2;
		tmp += dist(a, v[i]) + dist(t, v[i]);
		ans = min(ans, tmp);
		
		tmp = totA;
		tmp -= dist(t, v[i])*2;
		tmp += dist(b, v[i]) + dist(t, v[i]);
		ans = min(ans, tmp);
	}
	
	
	cout << fixed << setprecision(12) << min(ans, solve(0, 0, 0)) << "\n";
	
	return 0;
}
