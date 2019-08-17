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

int n, q;
vector<int> block[600];//armazena os blocos ordenados para fazer a busca binaria
int block_size = 600;
int v[100010];

int ini(int blocoAtual){ return blocoAtual*block_size; }
int fim(int blocoAtual){ return min((blocoAtual+1)*block_size-1, n-1); }

int func(int blocoAtual, int X){//retorna quantos elementos são <= X no bloco
	int ans = upper_bound(block[blocoAtual].begin(), block[blocoAtual].end(), X) - block[blocoAtual].begin();
	return ans;
}

void update(int pos, int val){//atualiza só o bloco
	int valAntigo = v[pos];
	int blocoAtual = pos / block_size;
	v[pos] = val;
	
	for(int i = 0; i < block[blocoAtual].size(); i++){
		if(block[blocoAtual][i] == valAntigo){//achou o elemento procurado (pode ser qualquer ocorrencia dele, pois está tudo embaralhado em relação ao vetor original)
			block[blocoAtual][i] = val;//atualiza
			break;
		}
	}
	sort(block[blocoAtual].begin(), block[blocoAtual].end()); //ordena o bloco de novo
}

int query(int L, int R, int X){
	int blocoL, blocoR;
	blocoL = L / block_size;
	blocoR = R / block_size;
	int pos;
	int ans = 0LL;
	
	for(pos = L; pos <= min(R, fim(blocoL)); pos++)//procura em pedaços de blocos que não estão totalmente contidos no intervalo
		if(v[pos] <= X) ans++;
	
	for (int i = blocoL+1; i <= blocoR-1; i++)//faz a busca binaria em blocos que estão totalmente contidos
		ans += func(i, X);
	
	for(pos = max(pos, ini(blocoR)); pos <= R; pos++)//mesma coisa do primeiro for
		if(v[pos] <= X) ans++;
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		block[i/block_size].pb(v[i]);//adiciona no bloco correspondente
	}
	for (int i = 0; i < block_size; i++)//ordena todos os blocos
	{
		if(block[i].size()==0) break;
		sort(block[i].begin(), block[i].end());
	}
	
	char op;
	int L, R, X, pos, val;
	for (int i = 0; i < q; i++)
	{
		cin >> op;
		if(op=='C'){
			cin >> L >> R >> X;
			cout << query(L-1, R-1, X) << "\n";
		}else{
			cin >> pos >> val;
			update(pos-1, val);
		}
	}
	
	
	
	
	
	return 0;
}
