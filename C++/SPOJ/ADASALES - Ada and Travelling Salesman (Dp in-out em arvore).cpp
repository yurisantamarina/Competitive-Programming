#include <bits/stdc++.h>

using namespace std;
#define inf 1e9
#define pb push_back
#define mp make_pair
#define MAXN 100010
typedef long long int ll;

ll in[MAXN][2];
ll out[MAXN][2];
int c[MAXN];
vector<int> g[MAXN];

bool folha(int u){
	return (int)g[u].size() == 1 && u!=0;
}

ll solve(int u, int pai, bool tem){
	if(in[u][tem]!=-1) return in[u][tem];
	if(folha(u)){
		return in[u][tem] = tem ? c[u] : 0;
	}
	
	ll ans = 0;
	int v;
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		if(tem){
			ans = max(ans, solve(v, u, true));
			ans = max(ans, c[u] + solve(v, u, false));
		}else{
			ans = max(ans, solve(v, u, false));
			ans = max(ans, -c[u] + solve(v, u, true));
		}
	}
	return in[u][tem] = ans;
}

void calcOut(int u, int pai){
	ll mx1F = 0;
	ll mx2F = 0;
	ll mx1T = 0;
	ll mx2T = 0;
	int v;
	
	for (int i = 0; i < (int)g[u].size(); i++)
	{
		v = g[u][i];
		if(v == pai) continue;
		
		if(in[v][0] > mx1F){
			mx2F = mx1F;
			mx1F = in[v][0];
		}else if(in[v][0] > mx2F){
			mx2F = in[v][0];
		}
		
		if(in[v][1] > mx1T){
			mx2T = mx1T;
			mx1T = in[v][1];
		}else if(in[v][1] > mx2T){
			mx2T = in[v][1];
		}
	}
	
	ll mxF, mxT;
	for (int e = 0; e < (int)g[u].size(); e++)
	{
		v = g[u][e];
		if(v == pai) continue;
		
		if(in[v][0] == mx1F) mxF = mx2F;
		else mxF = mx1F;
		
		if(in[v][1] == mx1T) mxT = mx2T;
		else mxT = mx1T;
		
		//tenta ir para o pai e depois para algum irmao
		//FFF
		out[v][0] = max(out[v][0], mxF);
		//FFT
		out[v][0] = max(out[v][0], -c[u] + mxT);
		//FTF
		out[v][0] = max(out[v][0], -c[v] + c[u] + mxF);
		//FTT
		out[v][0] = max(out[v][0], -c[v] + mxT);
		
		//TFF
		out[v][1] = max(out[v][1], c[v] + mxF);
		//TFT
		out[v][1] = max(out[v][1], c[v] - c[u] + mxT);
		//TTF
		out[v][1] = max(out[v][1], c[u] + mxF);
		//TTT
		out[v][1] = max(out[v][1], mxT);
		
		
		//indo para o out do pai agora
		out[v][0] = max(out[v][0], out[u][0]);
		out[v][0] = max(out[v][0], -c[v] + out[u][1]);
		
		out[v][1] = max(out[v][1], c[v] + out[u][0]);
		out[v][1] = max(out[v][1], out[u][1]);
		
		calcOut(v, u);
	}
	
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, u, v, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> c[i];
	}
	
	for (ll i = 0; i < n-1; i++)
	{
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	
	memset(in, -1, sizeof in);
	solve(0, 0, false);
	solve(0, 0, true);
	
	//calcula o out
	out[0][0] = -inf;
	out[0][1] = -inf;
	calcOut(0, 0);
	
	for (int i = 0; i < q; i++)
	{
		cin >> u;
		cout << max(in[u][0], out[u][0]) << "\n";
	}
	
	
	return 0;
}
