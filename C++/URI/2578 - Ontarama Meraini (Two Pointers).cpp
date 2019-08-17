#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101
typedef long long int ll;

int at[27], patt[27], acc[MAXN];
string s, t;

bool match(){
	for (int i = 0; i < 26; i++)
		if(patt[i] != at[i]) return false;
	return true;
}

void build(){
	int l = 0, r = (int)t.size()-1;
	for (int i = 0; i <= r; i++)
	{
		patt[t[i]-'a']++;
		at[s[i]-'a']++;
	}
	
	while (r < (int)s.size())
	{
		if(match()) acc[l] = 1;
		else acc[l] = 0;
		
		l++;
		r++;
		if(r == (int)s.size()) break;
		at[s[l-1]-'a']--;
		at[s[r]-'a']++;
	}
	for (int i = 1; i < (int)s.size(); i++)
		acc[i] += acc[i-1];
}

int get(int l, int r){
	if(l > r) return 0;
	return acc[r] - (l ? acc[l-1] : 0);
}

bool ok(int l, int r){
	return get(l, r - (int)t.size() + 1) > 0;
}

ll solve(){
	int r = 0;
	int n = (int)s.size();
	ll ans = 0LL;
	for (int l = 0; l < n; l++)
	{
		while(r < n && !ok(l, r)) r++;
		if(r == n) break;
		ans += (ll)n - r;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> s >> t;
	build();
	
	cout << solve() << "\n";
	
	return 0;
}
