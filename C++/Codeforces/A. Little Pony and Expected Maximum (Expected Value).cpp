#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
double p[MAXN];
int m, n;

double exp(double base, int e){
	if(e == 0) return 1.0;
	if(e == 1) return base;
	double aux = exp(base, e/2);
	aux = aux * aux;
	if(e & 1) aux = aux * base;
	return aux;
}

int main(){
	cin >> m >> n;
	p[1] = exp(1.0 / m, n);
	double ans = p[1];
	for (int i = 2; i <= m; i++)
	{
		p[i] = exp((double)i / m, n) - exp((double)(i-1) / m, n);
		//prob de sair só valores entre 1 e i menos a prob de so sair valores entre 1 e i-1
		ans += i * p[i];
	}
	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}
