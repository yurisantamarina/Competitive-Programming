#include <bits/stdc++.h>

using namespace std;
typedef long double ld;
#define MAXN 201010

int x[MAXN], y[MAXN], neg, pos, nulo, n;

ld dist(ld xx, ld yy, int x1, int y1){
	return hypotl(xx - x1, yy - y1);
}

ld getRaio(ld xCentro){
	ld raio = -1;
	for (int i = 0; i < n; i++)
	{
		ld deltaX = xCentro - (ld)x[i];
		ld deltaY = abs(y[i]);
		//~ cout << "v = " << v << "  k = " << k << endl;
		raio = max(raio, (deltaX * deltaX + deltaY * deltaY) / (2.0 * deltaY));
	}
	//~ cout << raio << endl;
	return raio;
}

ld solve1(){
	ld lo = -10000000.0, hi = 10000000.0, mid1, mid2, ans = 100000000000000000.0;
	ld d1, d2;
	for (int i = 0; i < 500; i++)
	{
		mid1 = (2.0 * lo + hi) / 3.0;
		mid2 = (lo + 2.0 * hi) / 3.0;
		
		d1 = getRaio(mid1);
		d2 = getRaio(mid2);
		
		//~ cout << "x1 = " << mid1 << "  raio = " << d1 << endl;
		//~ cout << "x2 = " << mid2 << "  raio = " << d2 << endl;
		if(d1 > d2){
			lo = mid1;
			ans = min(ans, d2);
		}else{
			hi = mid2;
			ans = min(ans, d1);
		}
	}
	
	return ans;
}

ld solve2(ld a){
	return getRaio(a);
}

int main(){
	scanf("%d", &n);
	int a;
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &x[i], &y[i]);
		if(y[i] < 0) neg++;
		else if(y[i] > 0) pos++;
		else{
			a = x[i];
			nulo++;
		}
	}
	
	if(nulo > 1 || (neg > 0 && pos > 0)){
		printf("-1\n");
		return 0;
	}
	
	ld ans;
	if(!nulo){
		ans = solve1();
	}else{
		ans = solve2(a);
	}
	
	cout << fixed << setprecision(20) << ans << "\n";
	
	return 0;
}
