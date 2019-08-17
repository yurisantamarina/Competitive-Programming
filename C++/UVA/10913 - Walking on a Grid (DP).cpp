#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};

int n;
int baixo = 0, esq = 1, dir = 2;
int dp[77][77][7][3];
int grid[77][77];

bool pode(int x, int y){
	return x>=0 && x<n && y>=0 && y<n;
}

int solve(int x, int y, int k, int direcao){
	if(k<0) return -1e9;
	if(x==n-1 && y==n-1) return dp[x][y][k][direcao] = 0;
	if(dp[x][y][k][direcao] != -1) return dp[x][y][k][direcao];
	//~ cout << x << " " << y << " " << k << " " << direcao << endl;
	
	int ans = -1e9;
	if(direcao == baixo){
		if(pode(x+1, y)) ans = max(ans, grid[x+1][y] + solve(x+1, y, grid[x+1][y] < 0 ? k-1 : k, baixo));
		if(pode(x, y+1)) ans = max(ans, grid[x][y+1] + solve(x, y+1, grid[x][y+1] < 0 ? k-1 : k, dir));
		if(pode(x, y-1)) ans = max(ans, grid[x][y-1] + solve(x, y-1, grid[x][y-1] < 0 ? k-1 : k, esq));
	}else if(direcao == esq){
		if(pode(x+1, y)) ans = max(ans, grid[x+1][y] + solve(x+1, y, grid[x+1][y] < 0 ? k-1 : k, baixo));
		if(pode(x, y-1)) ans = max(ans, grid[x][y-1] + solve(x, y-1, grid[x][y-1] < 0 ? k-1 : k, esq));
	}else{
		if(pode(x+1, y)) ans = max(ans, grid[x+1][y] + solve(x+1, y, grid[x+1][y] < 0 ? k-1 : k, baixo));
		if(pode(x, y+1)) ans = max(ans, grid[x][y+1] + solve(x, y+1, grid[x][y+1] < 0 ? k-1 : k, dir));
	}
	
	return dp[x][y][k][direcao] = ans;
}

//~ void path(int x, int y, int k, int direcao){
	//~ if(k<0) return;
	//~ if(x==n-1 && y==n-1) return;
	
	//~ int ans = -1e9;
	//~ if(direcao == baixo){
		//~ if(pode(x+1, y) && dp[x][y][k][direcao] == grid[x+1][y] + dp[x+1][y][grid[x+1][y] < 0 ? k-1 : k][baixo]){
			//~ cout << "Baixo" << "\n";
			//~ path(x+1, y, grid[x+1][y] < 0 ? k-1 : k, baixo);
		//~ }
		//~ if(pode(x, y+1) && dp[x][y][k][direcao] == grid[x][y+1] + dp[x][y+1][grid[x][y+1] < 0 ? k-1 : k][dir]){
			//~ cout << "Direita" << "\n";
			//~ path(x, y+1, grid[x][y+1] < 0 ? k-1 : k, dir);
		//~ }
		//~ if(pode(x, y-1) && dp[x][y][k][direcao] == grid[x][y-1] + dp[x][y-1][grid[x][y-1] < 0 ? k-1 : k][dir]){
			//~ cout << "Esquerda" << "\n";
			//~ path(x, y-1, grid[x][y-1] < 0 ? k-1 : k, esq);
		//~ }
	//~ }else if(direcao == esq){
		//~ if(pode(x+1, y) && dp[x][y][k][direcao] == grid[x+1][y] + dp[x+1][y][grid[x+1][y] < 0 ? k-1 : k][baixo]){
			//~ cout << "Baixo" << "\n";
			//~ path(x+1, y, grid[x+1][y] < 0 ? k-1 : k, baixo);
		//~ }
		//~ if(pode(x, y-1) && dp[x][y][k][direcao] == grid[x][y-1] + dp[x][y-1][grid[x][y-1] < 0 ? k-1 : k][dir]){
			//~ cout << "Esquerda" << "\n";
			//~ path(x, y-1, grid[x][y-1] < 0 ? k-1 : k, esq);
		//~ }
	//~ }else{
		//~ if(pode(x+1, y) && dp[x][y][k][direcao] == grid[x+1][y] + dp[x+1][y][grid[x+1][y] < 0 ? k-1 : k][baixo]){
			//~ cout << "Baixo" << "\n";
			//~ path(x+1, y, grid[x+1][y] < 0 ? k-1 : k, baixo);
		//~ }
		//~ if(pode(x, y+1) && dp[x][y][k][direcao] == grid[x][y+1] + dp[x][y+1][grid[x][y+1] < 0 ? k-1 : k][dir]){
			//~ cout << "Direita" << "\n";
			//~ path(x, y+1, grid[x][y+1] < 0 ? k-1 : k, dir);
		//~ }
	//~ }
	
//~ }

int main () {
	int k, caso=1;
	while (cin >> n >> k, n!=0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> grid[i][j];
			}
		}
		
		memset(dp, -1, sizeof dp);
		cout << "Case " << caso++ << ": ";
		if(k==0 && grid[0][0] < 0)
		{
			cout << "impossible\n";
			continue;
		}
		int ans = grid[0][0] + solve(0, 0, grid[0][0] < 0 ? k-1 : k, baixo);
		if(ans < -1e7){
			cout << "impossible\n";
		}else{
			cout << ans << "\n";
		}
		//~ path(0, 0, k, baixo);
	}
	
	
	
	
	
	
	
	
	
	return 0;
}
