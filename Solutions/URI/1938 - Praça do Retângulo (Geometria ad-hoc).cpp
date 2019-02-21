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
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
const ll MOD = 0;
const ll N = 0;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	bool operator < (pv other) const{
		return x < other.x;
	}
};

vector<pv> v;

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int n, x, y;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		v.pb(pv(x, y));
	}
	sort(v.begin(), v.end());
	
	int aux=1e9;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		aux = 1e9;
		for (int j = i+1; j < n; j++)
		{
			if(v[j].y < v[i].y && aux==1e9){
				ans++;
				aux = v[j].y;
			}
			if(v[j].y > aux && v[j].y < v[i].y){
				ans++;
				aux = v[j].y;
			}
		}
		
		aux = 1e9;
		for (int j = i+1; j < n; j++)
		{
			if(v[j].y > v[i].y && aux==1e9){
				ans++;
				aux = v[j].y;
			}
			if(v[j].y < aux && v[j].y > v[i].y){
				ans++;
				aux = v[j].y;
			}
		}
		
		
	}
	cout << ans << "\n";
	
	
	return 0;
}
