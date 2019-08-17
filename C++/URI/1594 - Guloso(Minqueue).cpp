#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 1010101

int v[MAXN];

struct minqueue{
	deque<int> q;
	minqueue(){}
	void reset(){
		q.clear();
	}
	
	void insert(ll val){
		while((int)q.size() > 0 && val > q.back()) q.pop_back();
		q.push_back(val);
	}
	
	void remove(int val){
		if(q.front() == val) q.pop_front();
	}
	
	int query(){
		return q.front();
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t, n, k, s;
	cin >> t;
	minqueue q;
	while (t--)
	{
		cin >> n >> k >> s;
		v[0] = s;
		for (int i = 1; i < n; ++i)
			v[i] = (1LL*v[i-1]*1103515245 + 12345) % (2147483648LL);
		
		q.reset();
		for (int i = 0; i < k; i++)
			q.insert(v[i]);
		int l = 0, r = k-1;
		
		ll ans = 0LL;
		while (r < n)
		{
			ans += q.query();
			q.remove(v[l]);
			l++; r++;
			if(r < n) q.insert(v[r]);
		}
		
		cout << ans << "\n";
	}
	
	
	return 0;
}
