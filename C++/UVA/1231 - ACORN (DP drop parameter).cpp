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
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}


int qtdTree, hMax, perde;
int cost[2010][2010];
//~ int dp[2010][2010];
int dp[2010];
int tree[2010];
int q;

int solve(){
	
	/*
		Estando em uma árvore X na altura H, as opções que tenho é continuar em X na altura H-1, ou então ir pra qualquer outra árvore K != X na altura H - perde. A resposta ótima pra uma altura H só depende da resposta ótima na altura H-1, para uma árvore X, ou então da resposta ótima da altura H - perde.
		Só preciso saber qual a resposta ótima de cada altura, e a resposta ótima pra cada árvore na altura H-1.
		A resposta ótima de uma altura H é o máximo da resposta ótima de cada uma das árvores na altura H.
		
		dp[h] - melhor resposta para uma altura H (precisa de todos os tree[i] calculados)
		tree[i] - melhor resposta na altura que to calculando, começando na árvore i
	*/
	
	int mx;
	memset(tree, 0, sizeof tree);
	for (int h = 0; h <= hMax; h++)
	{
		mx = 0;
		for (int i = 0; i < qtdTree; i++)
		{
			if(h - perde >= 0){
				tree[i] = max(tree[i], dp[h-perde]) + cost[i][h];//tento continuar na mesma árvore ou então pular pra qualquer uma
			}else{
				tree[i] = max(tree[i], 0) + cost[i][h];//só posso continuar na árvore que estou
			}
			mx = max(mx, tree[i]);
		}
		dp[h] = mx;//a resposta pra 'h' é a melhor resposta começando de todas as árvores
	}
	
	return dp[hMax];//ou então o máximo entre o tree[i] final, que é o o máximo começando em cada árvore na altura hMax.
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc, x;
	cin >> tc;
	while (tc--)
	{
		cin >> qtdTree >> hMax >> perde;
		memset(cost, 0, sizeof cost);
		for (int i = 0; i < qtdTree; i++)
		{
			cin >> q;
			while (q--)
			{
				cin >> x;
				cost[i][x]++;
			}
		}
		
		int ans = solve();
		cout << ans << "\n";
		//~ memset(dp, -1, sizeof dp);
		//~ int ans = 0;
		//~ for (int i = 0; i < qtdTree; i++)
		//~ {
			//~ ans = max(ans, solve(i, hMax));
		//~ }
		//~ cout << ans << endl;
	}
	
		
	return 0;
}
