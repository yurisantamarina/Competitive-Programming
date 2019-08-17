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
ll MOD = 1e6;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

struct mat{
	ll v[2][2];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat(int a, int b, int c, int d){
		v[0][0] = a;
		v[0][1] = b;
		v[1][0] = c;
		v[1][1] = d;
	}
	
	mat operator * (mat other){
		mat ans;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					ans.v[i][j] = (ans.v[i][j]%MOD + (v[i][k] * other.v[k][j])%MOD)%MOD;
				}
				
			}
			
		}
		return ans;
	}
};

mat ret(1,0,0,1), base;

mat exponencia(ll exp){
	if(exp==0) return ret;
	mat aux = exponencia(exp/2);
	aux = aux*aux;
	if(exp%2) aux = aux*base;
	return aux;
}

int main () {
	
	ll n, M, O;
	while (cin >> n >> M >> O)
	{
		M %= MOD;
		O %= MOD;
		base.v[0][0] = M;
		base.v[0][1] = O;
		base.v[1][0] = 1;
		base.v[1][1] = 0;
		n/=5LL;
		if(n==1){
			printf("%.06lld\n", M);
			continue;
		}
		
		mat aux = exponencia(n-1);
		printf("%.06lld\n", (aux.v[0][0]*M + aux.v[0][1])%MOD);
	}
	
	

	
	
	
	return 0;
}
