#include <bits/stdc++.h>

using namespace std;

int n;
string s;
int f[320];

bool ok(int sz){
	memset(f, 0, sizeof f);
	int cnt = 0;
	for (int i = 0; i < sz; i++)
	{
		f[s[i]]++;
		if(f[s[i]] == 1) cnt++;
	}
	int l = 0, r = sz-1;
	while (r < s.size())
	{
		if(cnt <= n) return true;
		f[s[l]]--;
		if(f[s[l]] == 0) cnt--;
		l++; r++;
		if(r >= s.size()) break;
		f[s[r]]++;
		if(f[s[r]] == 1) cnt++;
	}
	return false;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while (cin >> n, n)
	{
		//~ getchar();
		getline(cin, s);
		getline(cin, s);
		//~ cout << s << endl;
		int lo = 1, hi = s.size(), mid, ans = 0;
		while (lo <= hi)
		{
			mid = (lo+hi)/2;
			//~ printf("mid = %d\n", mid);
			if(ok(mid)){
				//~ printf("ok\n");
				ans = max(ans, mid);
				lo = mid+1;
			}else hi = mid-1;
		}
		cout << ans << "\n"; 
	}
	
	
	return 0;
}
