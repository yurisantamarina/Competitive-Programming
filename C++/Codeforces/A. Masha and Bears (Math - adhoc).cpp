#include <bits/stdc++.h>

using namespace std;

int main(){
	
	int f, m, s, r;
	cin >> f >> m >> s >> r;
	
	for (int big = 0; big <= 200; big++)
	{
		for (int mid = 0; mid < big; mid++)
		{
			for (int sm = 0; sm < mid; sm++)
			{
				if(2*f >= big && f <= big && 2*m >= mid && m <= mid && 2*s >= sm && s <= sm && r <= sm && 2*r >= sm && 2*r < big && 2*r < mid){
					cout << big << " " << mid << " " << sm << '\n';
					return 0;
				}
			}
		}
	}
	cout << "-1\n";
	
	
	return 0;
}
