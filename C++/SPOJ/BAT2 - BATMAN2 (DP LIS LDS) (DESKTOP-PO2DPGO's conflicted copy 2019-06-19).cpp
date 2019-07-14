#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
const ll MOD = 0;
const ll N = 0;

int v[200], n;
int dp[110][110][110];

bool pode1(int pos, int last){
	if(last==n+1) return true;
	if(v[last] < v[pos]) return true;
	return false;
}

bool pode2(int pos, int last){
	if(last==n+1) return true;
	if(v[last] > v[pos]) return true;
	return false;
}

int solve(int pos, int last1, int last2){
	if(pos==n) return 0;
	if(dp[pos][last1][last2]!=-1) return dp[pos][last1][last2];
	
	int ans = 0;
	
	ans = max(ans, solve(pos+1, last1, last2));//NAO PEGA NENHUM
	
	if(pode1(pos, last1)){//PEGA SO O PRIMEIRO
		ans = max(ans, 1 + solve(pos+1, pos, last2));
	}
	if(pode2(pos, last2)){//PEGA SO O SEGUNDO
		ans = max(ans, 1 + solve(pos+1, last1, pos));
	}
	if(pode1(pos, last1) && pode2(pos, last2)){//PEGA OS DOIS (DESNECESSARIO)
		ans = max(ans, 1 + solve(pos+1, pos, pos));
	}
	
	return dp[pos][last1][last2] = ans;
}

int main () {

	int t;
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}
		memset(dp, -1, sizeof dp);
		cout << solve(0, n+1, n+1) << "\n";
	}
	
	
	return 0;
}
