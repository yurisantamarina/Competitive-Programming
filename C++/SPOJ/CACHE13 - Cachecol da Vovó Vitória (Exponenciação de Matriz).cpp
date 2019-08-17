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
ll MOD = 1e9+7;

struct mat{
	ll v[3][3];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat operator * (mat other){
		mat ans;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					ans.v[i][j] += v[i][k] * other.v[k][j];
					ans.v[i][j]%=MOD;
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

/*
	F(1) = 6
	F(2) = 6
	
	F(i) = 2*F(i-1) + 2*F(i-2) + 0*F(i-3), se i for impar
	F(i) = 0*F(i-1) + 3*F(i-2) + 2*F(i-3), se i for par
	
	Para i impar:
	2 2 0
	1 1 0
	0 1 0
	
	Para i par:
	0 3 2
	1 0 0
	0 1 0
	
	
	2 2 0   0 3 2   3 2 0
	1 1 0 * 1 0 0 = 2 2 0    Vai intercalando, por isso precisa multiplicar as duas
	0 1 0   0 1 0   1 0 0
	
	ANS = F(2*N) + F(2*N - 1);
	
	F(2*N)        3 2 0     F(2)
	F(2*N - 1) =  2 2 0  *  F(1)
	F(2*N - 2)    1 0 0     F(0)
*/






int main () {
	ll n;
	cin >> n;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.v[i][j] = i==j;
		}
	}
	base.v[0][0] = 3;
	base.v[0][1] = 2;
	base.v[1][1] = 2;
	base.v[1][0] = 2;
	base.v[2][0] = 1;
	
	mat aux = exponencia(n-1);
	
	cout << (aux.v[0][0]*6 + aux.v[0][1]*6 + aux.v[1][0]*6 + aux.v[1][1]*6)%MOD << "\n";
	
	return 0;
}
