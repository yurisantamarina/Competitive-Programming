#include <bits/stdc++.h>

using namespace std;
#define pb push_back
typedef long long int ll;


int f[6060], v[2020], n, acc[60060];
vector<int> v2;

int main(){
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> v[i];
	
	sort(v, v+n);
	
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++){
			f[v[j] - v[i]]++;
			if(f[v[j] - v[i]] == 1) v2.pb(v[j] - v[i]);
		}
	
	for (int i = 5010-1; i >= 0; i--)
		acc[i] = acc[i+1] + f[i];
	
	sort(v2.begin(), v2.end());
	
	int sumAndrew;
	ll ans = 0LL;
	for (int i = 0; i < v2.size(); i++)
	{
		for (int j = 0; j < v2.size(); j++)
		{
			sumAndrew = v2[i] + v2[j];
			ans += (ll)acc[sumAndrew + 1] * (ll)f[v2[i]] * (ll)f[v2[j]];
		}
	}
	
	ll tot = ((ll)n*(n-1))/2;
	tot *= tot*tot;
	
	cout << fixed << setprecision(10) << 1.0*ans/tot << endl;
	
	return 0;
}
