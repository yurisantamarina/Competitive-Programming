#include <bits/stdc++.h>

#define MOD 1300031
#define MAXN 10010100

using namespace std;
typedef long long int ll;

int fat[MAXN];
int N, C, n;

void build(){
	fat[0] = 1;
	for (int i = 1; i < MAXN; i++)
		fat[i] = ((ll)fat[i-1] * i) % MOD;
}

int exp(int base, int e){
	if(e == 0) return 1;
	int aux = exp(base, e / 2);
	aux = ((ll)aux * aux) % MOD;
	if(e & 1) aux = ((ll)aux * base) % MOD;
	return aux;
}

int inv(int n){
	return exp(n, MOD - 2);
}

int solve(int N, int C){
	int num = fat[N + C - 1];
	int den = ((ll)fat[N - 1] * fat[C]) % MOD;
	return ((ll)num * inv(den)) % MOD;
}

int main(){
	int tc;
	
	build();
	cin >> tc;
	while (tc--)
	{
		cin >> N >> C;
		cout << solve(N, C) << "\n";
	}
	
	return 0;
}
