#include <bits/stdc++.h>

using namespace std;


int main(){
	int n, m;
	cin >> n >> m;
	if(n < m) swap(n, m);
	
	if(n > 6) cout << "0/1\n";
	else{
		int num = 6 - n + 1;
		int den = 6;
		int g = __gcd(num, den);
		num /= g;
		den /= g;
		printf("%d/%d\n", num, den);
	}
	return 0;
}
