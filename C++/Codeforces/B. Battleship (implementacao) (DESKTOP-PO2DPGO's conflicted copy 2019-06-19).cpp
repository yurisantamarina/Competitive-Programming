#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
int n, k;
char grid[120][120];
int cnt[120][120];

int main(){
	cin >> n >> k;
	int x = 0, y = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];
	
	int ans = 0;
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if(j + k - 1 < n){
				bool erro = false;
				for(int J = j; J < j + k; J++){
					if(grid[i][J] != '.'){
						erro = true;
						break;
					}
				}
				if(!erro){
					for(int J = j; J < j + k; J++){
						cnt[i][J]++;
						if(cnt[i][J] > ans){
							ans = cnt[i][J];
							x = i;
							y = J;
						}
					}
				}
			}
			
			if(i + k - 1 < n){
				bool erro = false;
				for(int I = i; I < i + k; I++){
					if(grid[I][j] != '.'){
						erro = true;
						break;
					}
				}
				if(!erro){
					for(int I = i; I < i + k; I++){
						cnt[I][j]++;
						if(cnt[I][j] > ans){
							ans = cnt[I][j];
							x = I;
							y = j;
						}
					}
				}
			}
		}
	}
	cout << x+1 << " " << y+1 << "\n";
	return 0;
}
