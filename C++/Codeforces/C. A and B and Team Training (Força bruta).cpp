#include <bits/stdc++.h>

using namespace std;
#define PI acos(-1)

int main(){
	int a, b, exp, nw;
	cin >> a >> b;
	
	int ans = 0;
	for (int i = 0; i < 501010; i++)
	{
		if(i*2 > a || i > b) break;
		
		exp = a  - i*2;
		nw = b - i;
		if(2*exp <= nw){
			ans = max(ans, i + exp);
		}else{
			ans = max(ans, i + nw/2);
		}
	}
	cout << ans << "\n";
	
	
	return 0;
}
