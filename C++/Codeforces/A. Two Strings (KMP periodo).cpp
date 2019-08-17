//~ http://codeforces.com/group/3qadGzUdR4/contest/101711/problem/A

#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long int ll;

int p[MAXN];

void kmp(string &s){
	p[0] = 0;
	int idx = 0;
	for (int i = 1; i < s.size(); i++)
	{
		while(idx > 0 && s[idx] != s[i])
			idx = p[idx-1];
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
	}
}

bool dentro(string &a, string &b){
	string s = a + "$" + b;
	kmp(s);
	for (int i = 0; i < s.size(); i++)
		if(p[i] == a.size()) return true;
	return false;
}

int solve(string &s){
	kmp(s);
	return s.size() - p[s.size()-1];
}

string merge(string &a, string &b){
	string s = b + "$" + a;
	kmp(s);
	int val = p[s.size() - 1];
	
	return a + b.substr(val);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string a, b, s, s2;
	bool fst = true;
	int ans, ans2;
	
	int tc;
	cin >> tc;
	while(tc--){
		cin >> a >> b;
		if(!fst) cout << "\n";
		fst = false;
		if(dentro(a, b)){
			ans = solve(b);
			cout << ans << "\n";
			cout << b.substr(0, ans) << "\n";
		}else if(dentro(b, a)){
			ans = solve(a);
			cout << ans << "\n";
			cout << a.substr(0, ans) << "\n";
		}else{
			s = merge(a, b);
			ans = solve(s);
			
			s2 = merge(b, a);
			ans2 = solve(s2);
			cout << max(ans, ans2) << "\n";
			if(ans > ans2) cout << s.substr(0, ans) << "\n";
			else cout << s2.substr(0, ans2) << "\n";
		}
	}
	
	
	
	return 0;
}

