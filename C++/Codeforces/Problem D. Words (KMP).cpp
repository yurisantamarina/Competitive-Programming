//algum prefixo de T deve ser igual a algum sufixo de S -> T + "$" + S
//o que restou de S (um prefixo) deve ser o inverso do que restou de T (o inverso de sufixo de T) -> rev(T) + "$" + S

//~ http://codeforces.com/group/eqgxxTNwgd/contest/101245/attachments

#include <bits/stdc++.h>

using namespace std;

#define MAXN 101010

string str1, str2;
int p1[MAXN];
int p2[MAXN];

void build(string& s1, string& s2){
	int idx;
	p1[0] = 0;
	
	for (int i = 1; i < (int)s1.size(); i++)
	{
		idx = p1[i-1];
		while(s1[idx] != s1[i] && idx > 0)
			idx = p1[idx-1];
		
		if(s1[idx] == s1[i])
			idx++;
		
		p1[i] = idx;
	}
	
	p2[0] = 0;
	for (int i = 1; i < (int)s2.size(); i++)
	{
		idx = p2[i-1];
		while(s2[idx] != s2[i] && idx > 0)
			idx = p2[idx-1];
		
		if(s2[idx] == s2[i])
			idx++;
		
		p2[i] = idx;
	}
}


bool ok(int tam, int n){
	return p2[n + tam] == tam;
}

int solve(int n){
	int longest = p1[n-1]; 
	
	int sz = (n-1) / 2;
	while (longest > 0)
	{
		if(ok(sz - longest, sz)) 
			return sz - longest;
		
		longest = p1[longest-1];
	}
	
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s, t, r;
	cin >> s >> t;
	if((int)s.size() != (int)t.size()){
		cout << "No\n";
		return 0;
	}
	
	str1 = t + "$" + s;
	r = t;
	reverse(r.begin(), r.end());
	str2 = r + "$" + s;
	
	build(str1, str2);
	
	int ans = solve((int)str1.size());
	if(ans == -1) cout << "No\n";
	else cout << "Yes\n" << ans << "\n";
}
