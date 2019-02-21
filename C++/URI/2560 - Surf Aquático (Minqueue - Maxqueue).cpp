#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 1010101

int v[MAXN];

struct minqueue{
	deque<int> mn, mx;
	minqueue(){}
	void reset(){
		mn.clear();
		mx.clear();
	}
	
	void insert(int val){
		while((int)mx.size() > 0 && val > mx.back()) mx.pop_back();
		mx.push_back(val);
		while((int)mn.size() > 0 && val < mn.back()) mn.pop_back();
		mn.push_back(val);
	}
	
	void remove(int val){
		if(mn.front() == val) mn.pop_front();
		if(mx.front() == val) mx.pop_front();
	}
	
	int query(){
		return mx.front() + mn.front();
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, n, k, s, sumAt, l, r;
	ll ans;
	minqueue q;
	while (cin >> n >> k)
	{
		for (int i = 0; i < n; i++)
			cin >> v[i];
		
		q.reset();
		sumAt = 0;
		for (int i = 0; i < k; i++){
			q.insert(v[i]);
			sumAt += v[i];
		}
		l = 0; r = k-1;
		
		ans = 0;
		while (r < n)
		{
			ans += (sumAt - q.query());
			q.remove(v[l]);
			sumAt -= v[l];
			l++; r++;
			if(r < n){
				q.insert(v[r]);
				sumAt += v[r];
			}
		}
		
		cout << ans << "\n";
	}
	
	
	return 0;
}
