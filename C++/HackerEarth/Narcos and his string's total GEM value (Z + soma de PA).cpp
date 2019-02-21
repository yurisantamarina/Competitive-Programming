#include <bits/stdc++.h>
 
using namespace std;
#define MAXN 201010
typedef long long int ll;
int z[MAXN];
string s, text;
 
void Z(){
	int n = (int)s.size(), l = 0, r = 0;
	z[0] = n;
	
	for (int i = 1; i < n; i++)
	{
		z[i] = 0;
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
	}
}
 
int getPeriodo(){
	int n = (int)s.size();
	
	for (int i = 1; i < n; i++)
	{
		if(z[i] == n - i){
			if(n % (n - z[i]) == 0) return n / (n - z[i]);
			return 1;
		}
	}
	
	return 1;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
		
	int tc;
	ll ans, a1, an, K, n;
	cin >> tc;
	while (tc--)
	{
		cin >> text >> K;
		s = text;
		Z();
		
		ll periodo = getPeriodo();
		K = K * periodo;
		text = text.substr(0, (int)text.size() / periodo);
		
		s = text + text;
		Z();
		
		n = (ll)s.size();
		ans = 0LL;
		for (int i = 0; i < (int)text.size(); i++)
		{
			if(z[i] > (int)text.size()){//se repete em PA
				a1 = (int)text.size();
				an = (int)text.size() * K;
				ans += ((a1 + an) * K) / 2;
			}else if(z[i] + i < (int)text.size()){//se repete dentro da string só
				ans += K*z[i];
			}else{//comeca dentro da string e acaba fora
				ans += z[i] * (K-1) + z[i+(int)text.size()];
			}
		}
		cout << ans << "\n";
		
	}
	
	
	
	return 0;
}
Language: C++14
