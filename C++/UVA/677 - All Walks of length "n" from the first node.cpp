#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (ll)floor(1 + log10((double)a))
#define digitCount(a, b) (ll)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};

int n;
char vis[1000];
vector<int> g[1000];

void limpa(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
		vis[i]=0;
	}
}
set<string> saida;

void solve(int u, int k, string s){
	//~ cout << u << " " << k << endl;
	if(k==0){
		saida.insert(s);
		return;
	}
	
	for (int i = 0; i < g[u].size(); i++)
	{
		int v = g[u][i];
		if(!vis[v]){
			vis[v]=1;
			solve(v, k-1, s+char(v+'0'));
			vis[v]=0;
		}
	}
	
	
}

int main(){
	bool fst=true;
	int lixo, k, x;
	while (cin >> n >> k)
	{
		limpa();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> x;
				if(x==1){
					g[i].pb(j);
					g[j].pb(i);
				}
			}
		}
		memset(vis, 0, sizeof vis);
		vis[0]=1;
		saida.clear();
		solve(0, k, "0");
		if(!fst) cout << endl;
		fst=false;
		
		if(saida.size()==0){
			cout << "no walk of length " << k << endl;
			cin >> lixo;
			continue;
		}
		for(auto s : saida){
			for (int i = 0; i < s.size(); i++)
			{
				if(i==0) cout << '(' << int(s[i]-'0' + 1);
				else cout << ',' << int(s[i]-'0'+1);
			}
			cout << ')' << endl;
			
		}
		cin >> lixo;
	}
	
	
	
	
	return 0;
}
