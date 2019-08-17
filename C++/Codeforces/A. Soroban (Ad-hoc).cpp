#include <bits/stdc++.h>

using namespace std;


int main(){
	int n;
	cin >> n;
	if(n == 0) cout << "O-|-OOOO" << endl;
	else{
		
		while(n){
			int x = n%10;
			
			if(x >= 5) cout << "-O|";
			else cout << "O-|";
			
			for (int i = 0; i < 5; i++)
			{
				if(i == x || i == x-5) cout << "-";
				else cout << "O";
			}
			cout << "\n";
			
			n/= 10;
		}
	}
	

	
	
	return 0;
}
