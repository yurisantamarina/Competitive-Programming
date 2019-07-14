#include <bits/stdc++.h>

using namespace std;
#define MAXN 400010

int sz, n, m;
int s[MAXN], a[MAXN], b[MAXN], p[MAXN];

void build(){
	sz = 0;
	
	for (int i = 1; i < m; i++)
		s[sz++] = b[i] - b[i-1];
	
	s[sz++] = 1e9+2;
	
	for (int i = 1; i < n; i++)
		s[sz++] = a[i] - a[i-1];
}

int kmp(){
	build();
	int idx, ans = 0;
	p[0] = 0;
	for (int i = 1; i < sz; i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
		
		p[i] = idx;
		if(p[i] == m-1) ans++;
	}
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for (int i = 0; i < n; i++)
		cin >> a[i];
	
	for (int i = 0; i < m; i++)
		cin >> b[i];
	
	if(m == 1) cout << n << "\n";
	else cout << kmp() << "\n";
	
	return 0;
}
