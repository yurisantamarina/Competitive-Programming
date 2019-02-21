#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN (int)2e5 + 10
int p[MAXN];
unordered_map<string, int> mapa;
vector<int> s;
string text[MAXN];
string pattern[MAXN];
int n, m;

bool kmp(){
	int idx;
	p[0] = 0;
	for (int i = 1; i < (int)s.size(); i++)
	{
		idx = p[i-1];
		while (s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
		
		p[i] = idx;
		if(p[i] == m-1) return true;
	}
	
	return false;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	mapa["A"] = 0;
	mapa["A#"] = 1;
	mapa["Bb"] = 1;
	mapa["B"] = 2;
	mapa["Cb"] = 2;
	mapa["B#"] = 3;
	mapa["C"] = 3;
	mapa["C#"] = 4;
	mapa["Db"] = 4;
	mapa["D"] = 5;
	mapa["D#"] = 6;
	mapa["Eb"] = 6;
	mapa["E"] = 7;
	mapa["Fb"] = 7;
	mapa["E#"] = 8;
	mapa["F"] = 8;
	mapa["F#"] = 9;
	mapa["Gb"] = 9;
	mapa["G"] = 10;
	mapa["G#"] = 11;
	mapa["Ab"] = 11;
	
	int x;
	while (cin >> n >> m)
	{
		if(!n && !m) break;
		for (int i = 0; i < n; i++)
			cin >> text[i];
			
		for (int i = 0; i < m; i++)
			cin >> pattern[i];
		
		if(m == 1){
			cout << "S\n";
			continue;
		}
		
		s.clear();
		for (int i = 1; i < m; i++)
		{
			x = mapa[pattern[i]] - mapa[pattern[i-1]];
			if(x < 0) x += 12;
			s.pb(x);
		}
		s.pb(1e9);
		for (int i = 1; i < n; i++)
		{
			x = mapa[text[i]] - mapa[text[i-1]];
			if(x < 0) x += 12;
			s.pb(x);
		}
		
		if(kmp()) cout << "S\n";
		else cout << "N\n";
	}
	
	
	
	return 0;
}
