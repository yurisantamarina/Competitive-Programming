#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define INF 100000000000000.0
typedef long long int ll;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	int operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
};

deque<pv> v;
vector<pv> tmp;
char memo[103][52];
double dp[103][52];
pv pivo;

int getQuad(pv a){
	a = a - pivo;
	if(a.x > 0 && a.y >= 0) return 1;
	if(a.x <= 0 && a.y > 0) return 2;
	if(a.x < 0 && a.y <= 0) return 3;
	return 4;
}

bool compare(pv a, pv b){
	int q1 = getQuad(a);
	int q2 = getQuad(b);
	if(q1 != q2) return q1 < q2;
	return ((a-pivo) ^ (b-pivo)) >= 0;
}

double solve(int pos, int falta){
	if(pos == (int)v.size()) return !falta ? 0.0 : INF;
	if(!falta) return INF;
	if(memo[pos][falta]) return dp[pos][falta];
	memo[pos][falta] = 1;
	
	int sz = 1;
	pv p[102];
	double area = 0.0, ans = INF;
	
	p[0] = pivo;
	
	for (int i = pos; i < (int)v.size(); i++)
	{
		while(sz > 2 && ((p[sz-1] - p[sz-2]) ^ (v[i] - p[sz-1])) <= 0){
			area -= (p[sz-1] ^ p[sz-2]);
			sz--;
		}
		p[sz++] = v[i];
		area += (p[sz-1] ^ p[sz-2]);
		
		if(((v[pos]-pivo) ^ (v[i] - pivo)) < 0) break;
		if(i-pos >= 1)
			ans = min(ans, fabs((pivo ^ v[i]) + area) + solve(i+1, falta-1));
	}
	
	return dp[pos][falta] = ans;
}

int main(){
	int n, B, x, y;
	while(scanf("%d %d", &B, &n) != EOF){
		if(B == 0 && n == 0) break;
		v.clear();
		tmp.clear();
		for (int i = 0; i < n; i++)
		{
			scanf("%d %d", &x, &y);
			if(i == 0) pivo = pv(x, y);
			else tmp.pb(pv(x, y));
		}
		
		sort(tmp.begin(), tmp.end(), compare);
		for (int i = 0; i < (int)tmp.size(); i++)
			v.pb(tmp[i]);
		
		double ans = INF;
		for (int i = 0; i < n-1; i++)
		{
			memset(memo, 0, sizeof memo);
			
			ans = min(ans, solve(0, B));
			v.pb(v[0]);
			v.pop_front();
		}
		
		printf("%.2lf\n", ans/2.0);
	}
	
}
