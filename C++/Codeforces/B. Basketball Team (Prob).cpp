#include <bits/stdc++.h>

using namespace std;

int n, m, h, qtd[1011];

int main(){
	int sum = 0;
	cin >> n >> m >> h;
	for (int i = 1; i <= m; i++)
	{
		cin >> qtd[i];
		sum += qtd[i];
	}
	
	if(sum < n){
		cout << "-1\n";
		return 0;
	}
	
	int falta = n - 1;
	int tot = sum - 1;
	int possible = sum - qtd[h];
	
	if(falta > possible){
		cout << "1\n";
		return 0;
	}
	
	double prob = 1.0;
	
	while (falta--)
	{
		prob *= (1.0*possible) / tot;
		possible--;
		tot--;
	}
	
	cout << fixed << setprecision(10);
	cout << 1 - prob << "\n";
	
	return 0;
}
