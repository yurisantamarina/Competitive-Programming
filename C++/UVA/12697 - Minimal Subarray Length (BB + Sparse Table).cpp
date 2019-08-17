#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define MAXN 501010
typedef long long int ll;
typedef pair<ll, int> pii;

int n, tc, x, lg = 0;
ll v[MAXN];

struct SparseTable{
	vector<vector<ll> > st;
	SparseTable(){
		
	}
	SparseTable(int len){
		st.resize(len + 2);
		for (int i = 0; i < len + 2; i++)
			st[i].resize(lg);
		
		for (int i = 0; i <= len; i++)
			st[i][0] = v[i];
		
		for(int j = 1; j < lg; j++){
			for(int i = 0; i + (1 << j) - 1 <= len; i++){
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	
	int query(int l, int r){
		int k = 31 - __builtin_clz(r - l + 1);
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
};

SparseTable st;

int bb(int i){
	int lo = 0, hi = i - 1, mid, ans = -3 * MAXN;
	//~ printf("oi\n");
	while (lo <= hi)
	{
		mid = (lo + hi) / 2;
		//~ printf("query [%d, %d] = %d  v[i] - x = %d\n", mid, i - 1, st.query(mid, i - 1), v[i] - x);
		if(st.query(mid, i - 1) <= v[i] - x){
			ans = max(ans, mid);
			lo = mid + 1;
		}else hi = mid - 1;
	}
	//~ printf("ans = %d\n", ans);
	return ans;
}

int main(){
	scanf("%d", &tc);
	int cnt = 0;
	while (tc--)
	{
		scanf("%d %d", &n, &x);
		//~ if(cnt == 30) printf("%d %d\n", n, x);
		v[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%lld", &v[i]);
			//~ if(cnt == 30) printf(" %lld", v[i]);
			v[i] += v[i - 1];
		}
		lg = 31 - __builtin_clz(n);
		lg++;
		//~ if(cnt == 30) printf("\n");
		
		st = SparseTable(n);
		
		int ans = n + 10;
		for (int i = 1; i <= n; i++)
		{
			int tmp = bb(i);
			ans = min(ans, i - tmp);
		}
		//~ cnt++;
		if(ans > n + 1) ans = -1;
		//~ if(cnt == 31)printf("%d\n", ans);
		printf("%d\n", ans);
	}
	
	return 0;
}
