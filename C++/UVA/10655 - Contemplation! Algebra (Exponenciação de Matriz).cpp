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


struct mat{
	ll v[2][2];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat operator * (mat other){
		mat ans;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					ans.v[i][j] += v[i][k] * other.v[k][j];
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
	ret.v[0][0]=1;
	ret.v[1][1]=1;
	
	ll p, q, n;
	while (cin >> p >> q >> n)
	{
		if(!p && !q && !n) break;
		base.v[0][0] = p;
		base.v[0][1] = -q;
		base.v[1][0] = 1;
		base.v[1][1] = 0;
		if(n==0){
			cout << 2 << "\n";
			continue;
		}
		mat ans = exponencia(n-1);
		cout << ans.v[0][0]*p + ans.v[0][1]*2 << "\n";
	}
	
	
	
	
	
	
	
	
	return 0;
}
