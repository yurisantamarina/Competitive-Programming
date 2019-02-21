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

int n, x;
int v[20];

double f(double irr){
	double sum = 0;
	
	for (int i = 1; i <= n; i++)
	{
		sum += (v[i]*1.0/(pow(1.0+irr, i)));
		//~ cout << pow(1.0+irr, i) << " ";
	}
	//~ cout << endl;
	return sum;
}

int main () {
	while (cin >> n, n!=0)
	{
		cin >> x;
		x = -x;
		for (int i = 1; i <= n; i++)
		{
			cin >> v[i];
		}
		
		double lo = -1, hi = 10000;
		double mid, aux;
		double ans=-1e9;
		for (int i = 0; i < 70; i++)
		{
			mid = (lo+hi)/2.0;
			//~ cout << "mid = " << mid << endl;
			aux = f(mid);
			//~ cout << fixed << setprecision(5) << f(mid) << endl;
			if(abs(aux-x) < 1e-8){
				ans = mid;
			}
			if(aux < x) hi = mid;
			else lo = mid;
		}
		
		if(ans > -1e9){
			cout << fixed << setprecision(2) << hi << endl;
		}else{
			cout << "No\n";
		}
	}	
	
	
	
	
	return 0;
}
