#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
#define MAXN 110
#define MAXM 1010
#define mp make_pair
#define F first
#define S second
#define pb push_back

struct node{
	int id, T, P;
	node(){}
	node(int a, int b, int c){
		id = a;
		T = b;
		P = c;
	}
	
	bool operator < (node other) const{
		return T * other.P < other.T * P;
	}
};


int n, Tmax;
pii dp[MAXN][MAXM];
node v[MAXN];

pii maxx(pii a, pii b){
	if(a.F == b.F) return mp(a.F, min(a.S, b.S));
	if(a.F > b.F) return a;
	return b;
}

pii operator + (pii a, pii b){
	return mp(a.F + b.F, a.S + b.S);
}

bool maior(pii a, pii b){
	if(a.F > b.F) return true;
	if(a.F == b.F){
		if(a.S < b.S) return true;
		return false;
	}
	return false;
}

int main(){
	cin >> n >> Tmax;
	int t, p, T, P;
	for (int i = 1; i <= n; i++){
		cin >> t >> p;
		v[i] = node(i, t, p);
	}
	
	sort(v+1, v+n+1);
	
	
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= Tmax; j++)
		{
			dp[i][j] = dp[i-1][j];
			if(j - v[i].T >= 0){
				if(maior(dp[i-1][j-v[i].T] + mp(v[i].P, j * v[i].P), dp[i][j])){
					dp[i][j] = dp[i-1][j-v[i].T] + mp(v[i].P, j * v[i].P);
				}
			}
			
		}
	}
	
	pii ans = mp(-1e9, 1e9), lst;
	for (int i = 0; i <= Tmax; i++)
	{
		if(maior(dp[n][i], ans)){
			ans = dp[n][i];
			lst = mp(n, i);
		}
	}
	
	vector<int> pegou;
	int i, j;
	while (lst.F > 0)
	{
		i = lst.F;
		j = lst.S;
		
		if(dp[i][j] == dp[i-1][j]){
			lst = mp(i-1, j);
		}else{
			pegou.pb(v[i].id);
			lst = mp(i-1, j-v[i].T);
		}
	}
	
	cout << (int)pegou.size() << "\n";
	for (int i = (int)pegou.size()-1; i >= 0; i--)
	{
		if(i < (int)pegou.size()-1) cout << " ";
		cout << pegou[i];
	}
	cout << "\n";
	
	
	
	
	return 0;
}
