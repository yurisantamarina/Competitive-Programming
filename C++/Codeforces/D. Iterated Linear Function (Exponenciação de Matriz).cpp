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
ll MOD = 1000000007;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

struct mat{
	ll v[2][2];
	mat(){}
	mat(int a, int b, int c, int d){
		v[0][0] = a;
		v[0][1] = b;
		v[1][0] = c;
		v[1][1] = d;
	}
	const mat operator * (mat a){
		mat b(0, 0, 0, 0);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					b.v[i][j] += (v[i][k] * a.v[k][j])%MOD;
					b.v[i][j] %= MOD;
				}
			}
		}
		
		return b;
	}
};

mat base;

mat exponencia(ll exp){
	if(exp==0) return mat(1, 0, 0, 1);
	mat aux = exponencia(exp / 2);
	aux = aux * aux;
	if(exp%2 != 0) aux = aux * base;
	
	return aux;
}

int main () {
	ll a, b, n, x;
	cin >> a >> b >> n >> x;
	base = mat(a, 1, 0, 1);
	
	base = exponencia(n);
	
	cout << (base.v[0][0]*x + base.v[0][1]*b)%MOD << "\n";
	

	
	
	
	return 0;
}
