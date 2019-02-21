#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define mp make_pair
#define F first
#define S second
int z[MAXN];
int cost[MAXN], acc[MAXN];
string s, aux, text, text2, patt;
pair<int, int> dp[MAXN];

void build(){
	text = aux;
	text2 = aux;
	
	int n = (int)aux.size();
	
	for (int i = 0; i < n; i++)
	{
		cost[i] = -1;
		
		acc[i] = 0;
		if(aux[i] == '?'){
			text[i] = 'a';
			text2[i] = 'b';
			if(i%2 == 0) swap(text[i], text2[i]);
			acc[i] = 1;
		}
		
		if(i) acc[i] += acc[i-1];
	}
}

int getCost(int l, int r){
	return acc[r] - (l ? acc[l-1] : 0);
}

void Z(){
	int l = 0, r = 0, n = (int)s.size();
	z[0] = 0;
	for (int i = 1; i < n; i++)
	{
		z[i] = 0;
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		while(i + z[i] < n && s[z[i]] == s[z[i] + i]) z[i]++;
		if(i+z[i]-1 >= r){
			l = i;
			r = i+z[i]-1;
		}
		if(z[i] == (int)patt.size())
			cost[i - 2] = getCost(i - (int)patt.size() - 1, i - 2);
	}
}

pair<int, int> operator + (pair<int, int> a, pair<int, int> b) {
	return mp(a.F+b.F, a.S+b.S);
}

pair<int, int> maxx(pair<int, int> a, pair<int, int> b){
	if(a.F > b.F) return a;
	if(a.F < b.F) return b;
	return mp(a.F, min(a.S, b.S));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int m, n;
	cin >> n;
	cin >> aux;
	cin >> m;
	
	patt = "";
	for (int i = 0; i < m; i++)
	{
		if(i%2==0) patt += 'a';
		else patt += 'b';
	}
	
	build();
	
	s = patt + "$" + text;
	Z();
	s = patt + "$" + text2;
	Z();
	
	for (int i = 0; i < n; i++)
	{
		dp[i] = i ? dp[i-1] : mp(0, 0);
		if(cost[i] != -1){
			dp[i] = maxx(dp[i], dp[i-m] + mp(1, cost[i]));
		}
	}
	cout << dp[n-1].S << "\n";
	
	return 0;
}
