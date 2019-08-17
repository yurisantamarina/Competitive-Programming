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
const int MOD = 1e9 + 7;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

int n;

struct mat{
	ll v[101][101];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat operator * (mat other){
		mat ans;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
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
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int m, u, v, d;
	for (int i = 0; i < 101; i++)
	{
		ret.v[i][i] = 1;
	}
	
	while (cin >> n >> m, n!=0)
	{
		base = mat();
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v;
			u--; v--;
			base.v[u][v]++;
			base.v[v][u]++;
		}
		
		cin >> u >> v >> d;
		u--; v--;
		mat aux = exponencia(d);
		
		if(aux.v[u][v]) cout << "Yes, Teobaldo can travel.\n";
		else cout << "No, Teobaldo can not travel.\n";
	}
		
		
	return 0;
}
