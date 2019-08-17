//~ http://codeforces.com/problemset/problem/356/A

#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
int ans[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q, l, r, win;
	set<int> s;
	
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		s.insert(i+1);
	
	while (q--)
	{
		cin >> l >> r >> win;
		
		for(auto it = s.lower_bound(l); it != s.end() && *it <= r;){
			if(*it == win) it++;
			else{
				ans[*it] = win;
				it = s.erase(it);
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << ans[i+1] << " ";
	cout << "\n";
	
	
	
	return 0;
}
