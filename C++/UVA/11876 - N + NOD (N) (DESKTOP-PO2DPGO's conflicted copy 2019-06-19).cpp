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
int dc[] = {-1,0,0, 1,1, 1,-1,-1};

int v[100010];

int func(int n){
	int ans=0;
	double r = sqrt(n);
	int raiz = r;
	if(raiz==r) ans=1;
	for (int i = 1; i < sqrt(n); i++)
	{
		if(n%i==0){
			//~ cout << i << " " << n/i << " ";
			ans+=2;
		}
	}
	//~ cout << endl;
	return ans;
}

int main () {
	v[0] = 1;
	
	for (int i = 1; i <= 100000; i++)
	{
		v[i] = v[i-1] + func(v[i-1]);
	}
	
	int t, a, b;
	cin >> t;
	int caso=1;
	while (t--)
	{
		cin >> a >> b;
		int p1 = lower_bound(v, v+100000, a)-v;
		int p2 = upper_bound(v, v+100000, b)-v;
		cout << "Case " << caso++ << ": " << (p2 - p1) << endl;
	}
	
	
	
	
	return 0;
}
