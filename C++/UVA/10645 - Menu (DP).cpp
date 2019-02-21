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
const int N = 0;
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

typedef pair<double, int> pdi;

#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

struct dishe{
	int benefit;
	int cost;
};

dishe v[60];
pdi dp[22][101][51];
char memo[22][101][51];
int budget, qtdDias, qtdDishes;

pdi operator + (pdi a, pdi b){
	return mp(a.F+b.F, a.S+b.S);
}

pdi max_(pdi a, pdi b){
	if(a.F==b.F){
		return mp(a.F, min(a.S, b.S));
	}
	if(a.F > b.F) return a;
	return b;
}

vector<int> saida;

bool operator == (pdi a, pdi b){
	return a.F == b.F && a.S == b.S;
}

pdi solve(int dia, int falta, int lst){
	if(falta < 0) return mp(-10000000000.0, 100000000);
	if(dia == qtdDias) return dp[dia][falta][lst] = mp(0.0, 0);
	if(memo[dia][falta][lst]) return dp[dia][falta][lst];
	memo[dia][falta][lst] = 1;
	pdi ans = mp(-10000000000.0, 100000000);
	
	for (int i = 0; i < qtdDishes; i++)
	{
		if(i == lst){
			ans = max_(ans, mp(0.0, v[i].cost) + solve(dia+1, falta-v[i].cost, i));
			
		}else{
			ans = max_(ans, mp(v[i].benefit, v[i].cost) + solve(dia+1, falta-v[i].cost, i));
			if(dia+2 <= qtdDias){
				ans = max(ans, mp(1.5*v[i].benefit, 2*v[i].cost) + solve(dia+2, falta-2*v[i].cost, i));
			}
		}
	}
	
	
	return dp[dia][falta][lst] = ans;
}

void path(int dia, int falta, int lst){
	if(falta < 0) return;
	if(dia == qtdDias) return;
	pdi ans = mp(-10000000000.0, 100000000);
	
	for (int i = 0; i < qtdDishes; i++)
	{
		if(i == lst){
			if(dp[dia][falta][lst] == mp(0.0, v[i].cost) + solve(dia+1, falta-v[i].cost, i)){
				saida.pb(i+1);
				path(dia+1, falta-v[i].cost, i);
				return;
			}
			//~ ans = max_(ans, mp(0.0, v[i].cost) + solve(dia+1, falta-v[i].cost, i));
			
		}else{
			
			if(dp[dia][falta][lst] == mp(v[i].benefit, v[i].cost) + solve(dia+1, falta-v[i].cost, i)){
				saida.pb(i+1);
				path(dia+1, falta-v[i].cost, i);
				return;
			}
			//~ ans = max_(ans, mp(v[i].benefit, v[i].cost) + solve(dia+1, falta-v[i].cost, i));
			
			
			if(dia+2 <= qtdDias){
				if(dp[dia][falta][lst] == mp(1.5*v[i].benefit, 2*v[i].cost) + solve(dia+2, falta-2*v[i].cost, i)){
					saida.pb(i+1);
					saida.pb(i+1);
					path(dia+2, falta-2*v[i].cost, i);
					return;
				}
				//~ ans = max(ans, mp(1.5*v[i].benefit, 2*v[i].cost) + solve(dia+2, falta-2*v[i].cost, i));
			}
		}
	}
	
	
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	while (1)
	{
		scanint(qtdDias);
		scanint(qtdDishes);
		scanint(budget);
		if(!qtdDias && !qtdDishes && !budget) break;
		for (int i = 0; i < qtdDishes; i++)
		{
			//~ cin >> v[i].cost >> v[i].benefit;
			scanint(v[i].cost);
			scanint(v[i].benefit);
		}
		memset(memo, 0, sizeof memo);
		
		pdi ans = solve(0, budget, qtdDishes);
		//~ cout << ans.F << " " << ans.S << endl;
		if(ans.F < 0){
			//~ cout << "0.0\n\n";
			printf("0.0\n\n");
		}else{
			saida.clear();
			path(0, budget, qtdDishes);
			printf("%.1lf\n", ans.F);
			//~ cout << fixed << setprecision(1) << ans.F << "\n";
			for (int i = 0; i < saida.size(); i++)
			{
				if(i) printf(" ");
				printf("%d", saida[i]);
				//~ cout << saida[i];
			}
			printf("\n");
			
		}
		
	}
	
	return 0;
}
