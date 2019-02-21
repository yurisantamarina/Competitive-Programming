//~ R Z R Z R Z R Z R Z R Z R Z
//~ A
//~ E E A
//~ E E E E A
//~ E E E E E E A
//~ E E E E E E E E A
//~ ....
//~ Ar + (Er * Ez)^1 * Ar + (Er * Ez)^2 * Ar + (Er * Ez)^3 * Ar....
//~ Soma de PG infinita com razao -1 < q < 1: S = a1 / (1 - q)

#include <bits/stdc++.h>

using namespace std;
#define LIM 1000000
int a, b, c, d;
double Ar, Az, Er, Ez;

int main(){
	cin >> a >> b >> c >> d;
	Ar = (a*1.0) / (b*1.0);
	Az = (c*1.0) / (d*1.0);
	Er = 1 - Ar;
	Ez = 1 - Az;
	
	cout << fixed << setprecision(10) << (Ar / (1 - Er * Ez)) << "\n";
	
	return 0;
}
