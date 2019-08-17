#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;

int n, m, yl[65], yr[65];
pii mat[65][65];
vector<ll> maskL, maskR;

pii getY(int y1, int y2){
	int vy = y2 - y1;
	
	int num = 2 * y1 + vy;
	int den = 2;
	int g = __gcd(num, den);
	
	return mp(num / g, den / g);
}

void update(int a, int b){
	pii p = mat[a][b];
	
	ll mask1 = 0LL, mask2 = 0LL;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if(mat[i][j] == mat[a][b]){
				mask1 |= (1LL << i);
				mask2 |= (1LL << j);
			}
	
	maskL.pb(mask1);
	maskR.pb(mask2);
}

int main(){
	
	vector<pii> possible;
	
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; i++)
		scanf("%d", &yl[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d", &yr[i]);
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			mat[i][j] = getY(yl[i], yr[j]);
	
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			update(i, j);
	
	for (int i = 0; i < (int)maskL.size(); i++)
		for (int j = 0; j < (int)maskR.size(); j++)
			ans = max(ans, __builtin_popcountll(maskL[i] | maskL[j]) + __builtin_popcountll(maskR[j] | maskR[i]));
			
	printf("%d\n", ans);
	
	return 0;
}
