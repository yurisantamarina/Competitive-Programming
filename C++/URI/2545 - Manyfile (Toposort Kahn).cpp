#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef long double ld;
#define EPS 1e-9
#define PI acos(-1)
#define MAXN 1010
#define INF 1000000000
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
int n;
vector<int> g[MAXN];
int grau[MAXN];
char vis[MAXN];

void reset(){
	for (int i = 0; i < n; i++)
	{
		g[i].clear();
		vis[i] = 0;
		grau[i] = 0;
	}
	
}

int solve(int u){
	queue<pair<int, int> > q;
	q.push(mp(1, u));
	
	int aux, at;
	while (!q.empty())
	{
		u = q.front().S;
		aux = q.front().F;
		q.pop();
		at = aux;
		vis[u] = 1;
		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			grau[v]--;
			if(grau[v] == 0) q.push(mp(aux+1, v));
		}
		g[u].clear();
	}
	
	return at;
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int x, u;
	int ans;
	while (scanf("%d", &n)!=EOF)
	{
		ans = 0;
		reset();
		for (int i = 0; i < n; i++)
		{
			//~ cin >> x;
			scanint(x);
			while (x--)
			{
				//~ cin >> u;
				scanint(u);
				u--;
				g[u].pb(i);
				grau[i]++;
			}
			
		}
		
		for (int i = 0; i < n; i++)
		{
			if(!vis[i]){
				if(grau[i] == 0) ans = max(ans, solve(i));
			}
		}
		
		bool erro = false;
		for (int i = 0; i < n; i++)
		{
			if(!vis[i]){
				erro = true;
				break;
			}
		}
		if(erro){
			puts("-1");
			//~ cout << "-1\n";
		}else{
			printf("%d\n", ans);
			//~ cout << ans << "\n";
		}
	}
	
	
	
	
	return 0;
}
