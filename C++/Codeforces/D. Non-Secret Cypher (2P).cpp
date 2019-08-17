#include <bits/stdc++.h>

using namespace std;
#define MAXN 401010
typedef long long int ll;

int n, k, v[MAXN], occ[MAXN], mx = -1;
unordered_map<int, int> f;

bool ok(){
	return mx >= k;
}

void add(int pos){
	if(pos == n) return;
	int val = v[pos];
	occ[f[val]]--;
	f[val]++;
	occ[f[val]]++;
	mx = max(mx, f[val]);
}

void del(int pos){
	int val = v[pos];
	occ[f[val]]--;
	f[val]--;
	occ[f[val]]++;
	
	for(int i = mx; i >= 0; i--){
		if(occ[i]){
			mx = i;
			break;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	int r = -1;
	ll ans = 0LL;
	for (int l = 0; l < n; l++)
	{
		while(r < n && !ok()){
			r++;
			add(r);
		}
		if(ok()){
			ans += n - r;
			//~ cout << "ok " << l << " " << r << endl;
		}
		del(l);
		if(l == r){
			r++;
			add(r);
		}
	}
	cout << ans << "\n";
	
	
	return 0;
}
