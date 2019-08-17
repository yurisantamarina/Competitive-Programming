#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const ll MOD = 0;
const ll N = 0;

int v[100010], n;

bool can(int k){
	int d;
	for (int i = 0; i < n; i++)
	{
		if(i) d = v[i]-v[i-1];
		else d = v[i];
		if(d > k) return false;
		if(d==k) k--;
	}
	return k>=0;
}

int main () {
	int t;
	cin >> t;
	int caso=1;
	while (t--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> v[i];
		
		int lo = 0, hi = 100000000;
		int mid;
		while (lo+1 < hi)
		{
			mid = (lo+hi)/2;
			if(can(mid)) hi = mid;
			else lo = mid;
		}
		
		cout << "Case " << caso++ << ": " << hi << endl;
	}
	
	
	
	return 0;
}
