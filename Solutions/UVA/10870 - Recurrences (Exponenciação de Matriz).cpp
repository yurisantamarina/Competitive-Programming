#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
ll MOD;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

ll d;

struct mat{
	ll v[15][15];
	mat(){
		memset(v, 0, sizeof v);
	}
	
	const mat operator * (mat a){
		mat ans;
		for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < d; j++)
			{
				for (int k = 0; k < d; k++)
				{
					ans.v[i][j] += v[i][k] * a.v[k][j];
					ans.v[i][j] %= MOD;
				}
			}
		}
		return ans;
	}
};

mat base, ret;

mat exponencia(int exp){
	if(exp==0) return ret;
	
	mat aux = exponencia(exp / 2);
	aux = aux*aux;
	
	if(exp%2 != 0) aux = aux * base;
	
	return aux;
}

int main () {
	ll n;
	ll f[20];
		
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	while (cin >> d >> n >> MOD)
	{
		if(!n && !d && !MOD) break;
		base = mat();
		for (int i = 0; i < d; i++)
		{
			cin >> base.v[0][i];
		}
		
		int aux=0;
		ret = mat();
		
		ret.v[0][0] = 1;
		for (int i = 1; i < d; i++)
		{
			base.v[i][aux++] = 1;
			ret.v[i][i] = 1;
		}
		
		for (int i = 0; i < d; i++)
		{
			cin >> f[i];
		}
		
		n--;
		if(n<d){
			cout << f[n] << "\n";
		}else{
			mat ans = exponencia(n-d+1);
			ll anss = 0LL;
			
			aux=0;
			for (int i = d-1; i >= 0; i--)
			{
				anss += f[i]*ans.v[0][aux++];
				anss %= MOD;
			}
			cout << anss << "\n";
		}
		
	}
	
	
	
	return 0;
}
