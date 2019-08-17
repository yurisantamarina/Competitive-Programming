#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define MAXN 500110

int n;
int v[MAXN];
int suf[MAXN];
int pref[MAXN];

void build(ll need){
	ll sumPref = 0, sumSuf = 0;
	
	for (int i = 1, j = n; i <= n; i++, j--)
	{
		sumPref += v[i];
		sumSuf  += v[j];
		if(sumPref == need) pref[i] = 1;
		if(sumSuf  == need) suf[j]  = 1;
		suf[j] += suf[j+1];
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	
	ll sum = 0LL;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		sum += v[i];
	}
	
	if(sum%3 != 0){
		cout << "0\n";
		return 0;
	}
	
	build(sum / 3);
	
	
	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
	{
		if(pref[i]){
			ans += suf[i+2];
		}
	}
	cout << ans << "\n";
	
	
	return 0;
}
