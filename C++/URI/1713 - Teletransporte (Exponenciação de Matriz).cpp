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
llu MOD = 10000;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

int n, origem, destino, tam;

struct mat{
	int v[101][101];
	mat(){
		memset(v, 0, sizeof v);
	}
	
	const mat operator * (mat a){
		mat ans;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					ans.v[i][j] += v[i][k] * a.v[k][j];
					ans.v[i][j] %= MOD;
				}
			}
		}
		return ans;
	}
};

mat g, ret;

mat exponencia(int exp){
	if(exp==0) return ret;
	
	mat aux = exponencia(exp / 2);
	aux = aux * aux;
	
	if(exp%2 != 0) aux = aux * g;
	
	return aux;
}

int main () {
	int a, b, c, d;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			ret.v[i][j] = i==j;
		}
	}
	
	while (cin >> n >> tam)
	{
		cin >> origem >> destino;
		origem--;
		destino--;
		g = mat();
		for (int i = 0; i < n; i++)
		{
			cin >> a >> b >> c >> d;
			a--; b--; c--; d--;
			g.v[i][a]++;
			g.v[i][b]++;
			g.v[i][c]++;
			g.v[i][d]++;
		}
		mat ans = exponencia(tam);
		cout << ans.v[origem][destino] << "\n";
	}
	
	
	
	
	
	return 0;
}
