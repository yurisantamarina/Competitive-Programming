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
ll MOD = 13371337LL;

struct mat{
	ll v[5][5];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat operator * (mat other){
		mat ans;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					ans.v[i][j] += v[i][k] * other.v[k][j];
					ans.v[i][j]%=MOD;
					//~ while(ans.v[i][j] < -MOD) ans.v[i][j]+=MOD;
					//~ while(ans.v[i][j] > MOD) ans.v[i][j]-=MOD;
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
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	ll n, a, b, c, d;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ret.v[i][j] = i==j;
		}
	}
	base.v[0][0] = 2;
	base.v[0][4] = -1;
	base.v[1][0] = 1;
	base.v[2][1] = 1;
	base.v[3][2] = 1;
	base.v[4][3] = 1;
	
	while (cin >> n)
	{
		if(n==0) break;
		cin >> a >> b >> c >> d;
		
		mat ans = exponencia(n-4);
		
		//~ for (int i = 0; i < 5; i++)
		//~ {
			//~ for (int j = 0; j < 5; j++)
			//~ {
				//~ cout << ans.v[i][j] << " ";
			//~ }
			//~ cout << endl;
		//~ }
		
		ll aux = (ans.v[0][0]*(a+b+c+d) + ans.v[0][1]*d + ans.v[0][2]*c + ans.v[0][3]*b + ans.v[0][4]*a)%MOD;
		while (aux < 0)
		{
			aux+=MOD;
		}
		
		cout << aux%MOD << "\n";
	}
	
	
	
	
	return 0;
}
