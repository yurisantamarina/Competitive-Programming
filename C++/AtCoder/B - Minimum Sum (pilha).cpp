#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
int n, v[MAXN], l[MAXN], r[MAXN];
stack<int> p;
int main(){
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		while(!p.empty() && v[p.top()] > v[i])
			p.pop();
		l[i] = p.empty() ? 0 : p.top();
		p.push(i);
	}
	
	while(!p.empty())
		p.pop();
		
	long long ans = 0LL;
	for (int i = n; i >= 1; i--)
	{
		while(!p.empty() && v[p.top()] > v[i])
			p.pop();
		r[i] = p.empty() ? n + 1 : p.top();
		p.push(i);
		
		ans += (long long)v[i] * (i - l[i]) * (r[i] - i);
	}
	cout << ans << "\n";
	
	return 0;
}
