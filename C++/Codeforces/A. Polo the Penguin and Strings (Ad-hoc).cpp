#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
int n, k;

int main(){
	cin >> n >> k;
	if(k > n || k == 1){
		if(n == 1 && k == 1) cout << "a\n";
		else cout << "-1\n";
		return 0;
	}
	
	if(k == 2){
		for (int i = 0; i < n; i++)
			cout << char('a' + i%2);
		cout << "\n";
	}else{
		int faltaK = k-2;
		for (int i = 0; i < n - faltaK; i++)
			cout << char('a' + i%2);
		for (int i = 0; i < faltaK; i++)
			cout << char('c' + i);
		cout << "\n";
	}
	
	return 0;
}
