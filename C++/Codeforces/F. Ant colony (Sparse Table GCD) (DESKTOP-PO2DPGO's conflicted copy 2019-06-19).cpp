#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()
#define MAXN 101010
#define LOG 20

map<int, vector<int> > occ;
set<int> s;
map<int, int> mapa;
int st[MAXN][LOG], v[MAXN], n, q;

void build(){
	for (int i = 1; i <= n; i++){
		st[i][0] = v[i];
		occ[v[i]].push_back(i);
	}
	
	for (int j = 1; j < LOG; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			if(i + (1<<j) - 1 > n) break;
			st[i][j] = __gcd(st[i][j-1], st[i + (1<<(j-1))][j-1]);
		}
	}
}

int query(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
	int ans = __gcd(st[l][k], st[r-(1<<k)+1][k]);
	return ans;
}

int getQtd(int l, int r, int val){
	int R = upper_bound(all(occ[val]), r) - occ[val].begin();
	int L = lower_bound(all(occ[val]), l) - occ[val].begin();
	return max(0, R-L);
}

int solve(int l, int r){
	int g = query(l, r);
	
	return r-l+1-getQtd(l, r, g);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> v[i];
		//~ s.insert(v[i]);
	}
	//~ int idx = 1;
	//~ for(auto i : s)
		//~ mapa[i] = idx++;
	
	build();
	
	int l, r;
	cin >> q;
	while (q--)
	{
		cin >> l >> r;
		cout << solve(l, r) << "\n";
	}
	
	
	return 0;
}
