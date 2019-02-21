#include <bits/stdc++.h>

using namespace std;
#define PI acos(-1)

int main(){
	int r[120], n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> r[i];
	sort(r, r+n);
	
	double ans;
	if(n%2!=0){
		ans = r[0]*r[0]*PI;
		for (int i = 2; i < n; i+=2)
			ans += r[i]*r[i]*PI - r[i-1]*r[i-1]*PI;
	}else{
		ans = 0.0;
		for (int i = 1; i < n; i+=2)
			ans += r[i]*r[i]*PI - r[i-1]*r[i-1]*PI;
	}
	cout << fixed << setprecision(10) << ans << "\n";
	
	
	return 0;
}
