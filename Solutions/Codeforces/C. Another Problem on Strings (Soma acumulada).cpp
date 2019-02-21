#include <bits/stdc++.h>

using namespace std;

#define MAXN 500010
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 1000000000
typedef long long int ll;

int qtd[1000010];
int acc[1000010];

int main(){
	int k;
	string s;
	
	cin >> k;
	cin >> s;
	qtd[0]++;
	
	ll ans = 0LL;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if(s[i] == '1') acc[i+1] = acc[i] + 1;
		else acc[i+1] = acc[i] + 0;
		qtd[acc[i+1]]++;
		if(acc[i+1]-k >= 0){
			if(k == 0){
				if(s[i] == '0'){
					ans += qtd[acc[i+1] - k]-1;
					
				}
			}else{
				ans += qtd[acc[i+1] - k];
			}
		}
	}
	cout << ans << "\n";
	
	
	
	
	
	return 0;
}
