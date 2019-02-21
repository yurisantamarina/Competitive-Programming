#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define F first
#define S second
int r[MAXN];
int l[MAXN];
int v[MAXN];
int mx[MAXN];
int n;
stack<pair<int, int> > p;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		while(p.size() > 0 && v[i] <= p.top().F) p.pop();
		if(p.size() > 0) l[i] = p.top().S;
		else l[i] = 0;
		p.push(make_pair(v[i], i));
	}
	
	while(p.size()) p.pop();
	
	for (int i = n; i >= 1; i--)
	{
		while(p.size() > 0 && v[i] <= p.top().F) p.pop();
		if(p.size() > 0) r[i] = p.top().S;
		else r[i] = n+1;
		p.push(make_pair(v[i], i));
	}
	
	for (int i = 1; i <= n; i++)
		mx[r[i]-l[i]-1] = max(mx[r[i]-l[i]-1], v[i]);
	
	for (int i = n; i >= 1; i--)
		mx[i] = max(mx[i], mx[i+1]);
	for (int i = 1; i <= n; i++)
		cout << mx[i] << " ";
	cout << "\n";
	
	
}
