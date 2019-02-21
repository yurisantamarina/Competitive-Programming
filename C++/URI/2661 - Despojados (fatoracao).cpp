#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int fatora(ll n){
	int ans = 0;
	int entrou;
	for (int i = 2; n > 1 && i < 1000010; i++)
	{
		entrou = 0;
		while(n % i == 0){
			n /= i;
			entrou = 1;
		}
		ans += entrou;
	}
	if(n > 1) ans++;
	
	return ans;
}
int main(){
	ll n;
	cin >> n;
	int exp = fatora(n);
	cout << (1<<exp) - (exp+1) << "\n";
	return 0;
}
