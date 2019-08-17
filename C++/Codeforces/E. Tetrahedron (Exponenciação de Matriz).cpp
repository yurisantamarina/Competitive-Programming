#include <bits/stdc++.h>

#define ll long long
ll MOD = 1e9 + 7;
using namespace std;

struct mat{
	ll v[4][4];
	mat(){
		memset(v, 0, sizeof v);
	}
	mat(int op){
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if(op) v[i][j] = i!=j;
				else v[i][j] = i==j;
			}
		}
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

mat base(1), ret(0);

mat exponencia(ll exp){
	if(exp==0) return ret;
	mat aux = exponencia(exp/2);
	aux = aux*aux;
	if(exp%2!=0) aux = aux*base;
	
	return aux;
}

int main () {
	ll n;
	cin >> n;
	mat ans = exponencia(n);
	
	cout << ans.v[3][3] << "\n";
	
	
	
	return 0;
}
