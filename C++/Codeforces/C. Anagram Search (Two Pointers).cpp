#include <bits/stdc++.h>

using namespace std;
string s, p;
int fp[29], f[29];

void del(char c){
	if(c == '?') return;
	f[c-'a']--;
}

void add(char c){
	if(c == '?') return;
	f[c-'a']++;
}

bool ok(){
	for (int i = 0; i < 26; i++)
		if(f[i] > fp[i]) return false;
		
	return true;
}

int solve(){
	if((int)s.size() < (int)p.size()) return 0;
	
	for (int i = 0; i < (int)p.size(); i++)
		fp[p[i]-'a']++;
	
	int l = 0, r = (int)p.size()-1;
	
	for (int i = 0; i <= r; i++)
		add(s[i]);
	
	int ans = 0;
	while (r < (int)s.size())
	{
		if(ok()) ans++;
		
		if(r == (int)s.size()-1) break;
		del(s[l]);
		add(s[r+1]);
		r++;
		l++;
	}
	
	return ans;
}

int main(){
	
	cin >> s;
	cin >> p;
	cout << solve() << "\n";
	
	return 0;
}
