#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int tam;
string ent;
//~ ll ans=-1;
string ans="";

map<pair<int, pair<int, string> >, char> mapa;

bool ok(string a, string b){
	if(b.size() > a.size()) return true;
	if(b.size() < a.size()) return false;
	for (int i = 0; i < a.size(); i++)
	{
		if(a[i] > b[i]) return false;
	}
	
	
}

void solve(int pos, int bate, string s){
	//~ cout << pos << " " << bate << " " << s << endl;
	if(pos==tam){
		string ajuda="";
		int i=0;
		while (i < s.size() && s[i]=='0')
		{
			i++;
		}
		for (i = i; i < s.size(); i++)
		{
			ajuda+=s[i];
		}
		
		
		//~ stringstream ss(ajuda);
		//~ ll numero;
		//~ ss >> numero;
		if(ok(ans, ajuda)){
			//~ cout << ajuda << " " << s << endl;
			ans = ajuda;
		}
		//~ cout << s << endl;
		return;
	}
	
	
	int f[10];
	string aux="";
	memset(f, 0, sizeof f);
	for (int i = 0; i < s.size(); i++){
		f[s[i]-'0']++;
	}
	
	for (int i = 0; i < 10; i++)
	{
		aux += (f[i]+'0');
	}
	if(mapa.find(mp(pos, mp(bate, aux))) != mapa.end()) return;
	
	char c;
	if(!bate){
		for (int i = 9; i >= 0; i--)
		{
			if(f[i] < 2){
				c = i+'0';
				solve(pos+1, false, s + c);
			}
		}
	}else{
		if(f[ent[pos]-'0'] < 2) solve(pos+1, true, s + (ent[pos]));
		for (int i = (ent[pos]-'0')-1; i >= 0; i--)
		{
			if(f[i] < 2){
				c = i+'0';
				solve(pos+1, false, s + c);
			}
		}
		
	}
	mapa[mp(pos, mp(bate, aux))];
}

int main(){
 
	ll n;
	cin >> n;
	
	stringstream ss;
	ss << n;
	ss >> ent;
	tam = ent.size();
	
	solve(0, true, "");
	cout << ans << endl;
    return 0;
}
