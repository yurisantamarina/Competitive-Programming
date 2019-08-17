#include <bits/stdc++.h>

using namespace std;
#define MAXN 111

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
	int operator ^ (pv other){
		return x * other.y - y * other.x;
	}
	int operator * (pv other){
		return x * other.x + y * other.y;
	}
	long double norma(){
		return sqrtl((*this) * (*this));
	}
	bool operator < (pv other) const{
		if(x != other.x) return x < other.x;
		return y < other.y;
	}
};

int n;
pv poly[MAXN], p1[MAXN], p2[MAXN];


void convexHull(){
	sort(poly, poly + n);
	int i = 0, j = 0;
	for (int k = 0; k < n; k++){
		pv p = poly[k];
		while(i > 1 && ((p1[i - 1] - p1[i - 2]) ^ (p - p1[i - 1])) >= 0) i--;
		p1[i++] = p;
		while(j > 1 && ((p2[j - 1] - p2[j - 2]) ^ (p - p2[j - 1])) <= 0) j--;
		p2[j++] = p;
	}
	
	n = 0;
	for (int k = 0; k < j; k++)
		poly[n++] = p2[k];
	for(int k = i - 2; k > 0; k--)
		poly[n++] = p1[k];
}

int dist(int i, int j, int k){
	return abs((poly[k] - poly[i]) ^ (poly[j] - poly[i]));
}

long double solve(){
	int j = 1;
	//~ printf("n = %d\n", n);
	long double ans = 10000000000.0;
	for (int i = 0; i < n; i++){
		while(dist(i, (i + 1) % n, (j + 1) % n) > dist(i, (i + 1) % n, j))
			j = (j + 1) % n;
		ans = min(ans, (1.0 * dist(i, (i + 1) % n, j)) / (poly[(i + 1) % n] - poly[i]).norma());
	}
	return ans;
}

int main(){
	int caso = 1;
	while (scanf("%d", &n), n){
		for (int i = 0; i < n; i++)
			scanf("%d %d", &poly[i].x, &poly[i].y);
		convexHull();
		printf("Case %d: %.2Lf\n", caso++, solve());
	}
	
	return 0;
}
