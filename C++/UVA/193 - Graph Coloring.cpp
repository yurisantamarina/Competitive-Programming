#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};
vector<int> g[200];
int n, m;
int cor[200];
int black=1;
int white=0;

void limpa(){
	for (int i = 0; i < 110; i++)
	{
		g[i].clear();
	}
	
}

bool pode(int u){
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if(cor[v]==black) return false;
	}
	return true;
}


int ans;
vector<int> saida, vet;

int func(){
	int cnt=0;
	for (int i = 1; i <= n; i++)
	{
		if(cor[i]==black){
			cnt++;
			vet.pb(i);
		}
	}
	return cnt;
}

void solve(int u){
	if(u==n+1){
		vet.clear();
		int aux = func();
		if(aux > ans){
			ans = aux;
			saida = vet;
		}
		return;
	}
	
	if(pode(u)){
		cor[u] = black;
		solve(u+1);
		cor[u] = white;
		solve(u+1);
	}else solve(u+1);
}

int main () {
	int t, u, v;
	cin >> t;
	bool fst=true;
	while (t--)
	{
		cin >> n >> m;
		limpa();
		ans = 0;
		saida.clear();
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		memset(cor, white, sizeof cor);
		solve(1);
		
		//~ if(!fst) cout << endl;
		//~ fst=false;
		
		cout << ans << endl;
		for (int i = 0; i < saida.size(); i++)
		{
			if(i) cout << " ";
			cout << saida[i];
		}
		cout << endl;
		
	}
	
	
	return 0;
}
