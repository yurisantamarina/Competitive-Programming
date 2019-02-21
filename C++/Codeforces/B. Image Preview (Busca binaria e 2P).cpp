#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define MAXN 1000010
int n, mv, change, tot;
int acc[MAXN];
string s;

int getChange(int l, int r){
	if(l > r) return 0;
	if(l == 0) return acc[r];
	return acc[r]-acc[l-1];
}

int getCost1(int l, int r){
	int cost = getChange(n, r)*change + (r-n)*mv + (r-n+1);
	if(l >= n) return cost;
	cost += (r - n + 1)*mv;
	cost += (n - l - 1)*mv + getChange(l, n-1)*change + (n-l);
	
	return cost;
}

int getCost2(int l, int r){
	int cost = getChange(l, n)*change + (n-l)*mv + (n-l+1);
	if(r <= n) return cost;
	cost += (n-l+1)*mv;
	cost += (r - n - 1)*mv + getChange(n+1, r)*change + (r-n);
	
	return cost;
}

bool ok(int tam, int op){
	int l, r, cost;
	if(op == 1){
		l = 0 + n; r = l + tam-1;
		while (r >= n)
		{
			cost = getCost1(l, r);
			if(cost <= tot) return true;
			l--;
			r--;
		}
		return false;
	}else{
		r = n; l = r-tam+1;
		while (l < n)
		{
			cost = getCost2(l, r);
			if(cost <= tot)	return true;
			l++;
			r++;
		}
		return false;
	}
}

int solve(int op){
	int lo = 1, hi = n, mid, ans = 0;
	
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		if(ok(mid, op)){
			ans = max(ans, mid);
			lo = mid+1;
		}else hi = mid-1;
	}
	
	return ans;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> mv >> change >> tot;
	cin >> s;
	n = (int)s.size();
	s += s;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if(s[i]=='w') acc[i] = 1;
		if(i) acc[i] += acc[i-1];
	}
	
	
	int ans = max(solve(1), solve(2));
	//~ int ans = solve1();
	cout << ans << "\n";
	
	return 0;
}
