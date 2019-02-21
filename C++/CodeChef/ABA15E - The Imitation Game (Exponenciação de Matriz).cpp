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
ll MOD = 1000000007LL;
 
struct mat{
	ll v[4][4];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat operator * (mat other){
		mat ans;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					ans.v[i][j] += v[i][k] * other.v[k][j];
					ans.v[i][j] %= MOD;
				}
			}
		}
		return ans;
	}
};
 
mat base, ret;
 
mat exponencia(ll exp){
	if(exp==0) return ret;
	mat aux = exponencia(exp/2);
	aux = aux*aux;
	if(exp%2) aux = aux*base;
	return aux;
}
 
int main () {
	ll t, n;
	cin >> t;
	for (int i = 0; i < 4; i++)
	{
		ret.v[i][i] = 1;
	}
	
	base.v[0][0]=4;
	base.v[0][1]=1;
	base.v[0][3]=1;
	base.v[1][1]=3;
	base.v[1][2]=2;
	base.v[2][1]=1;
	base.v[3][3]=1;
	
	//~ for (int i = 0; i < 4; i++)
	//~ {
		//~ for (int j = 0; j < 4; j++)
		//~ {
			//~ cout << base.v[i][j] << " ";
		//~ }
		//~ cout << endl;
	//~ }
	
	
	while (t--)
	{
		cin >> n;
		mat aux = exponencia(n);
		ll ans = aux.v[0][0]*1 + aux.v[0][1]*1 + aux.v[0][2]*1 + aux.v[0][3]*2;
		cout << ans%MOD << "\n";
	}
	
	
	
	
	
	
	return 0;
}
