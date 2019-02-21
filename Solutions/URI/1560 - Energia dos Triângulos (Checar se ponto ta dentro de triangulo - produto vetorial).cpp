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

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
};

int cross(pv a, pv b){
	int c = a.x*b.y - a.y*b.x;
	if(c > 0) return 1;
	if(c < 0) return -1;
	return 0;
}

pv toVec(pv &a, pv &b){
	return b-a;
}

bool contido(pv &a, pv &b, pv &c, pv &p){
	//~ printf("Testando se (%d,%d) esta contido em (%d,%d) (%d,%d) (%d,%d)\n", p.x, p.y, a.x, a.y, b.x, b.y, c.x, c.y);
	int aux = cross(toVec(p, a), toVec(p, b));
	if(cross(toVec(p, b), toVec(p, c))==aux && cross(toVec(p, c), toVec(p, a))==aux)
		return true;
	return false;
}

vector<pv> preto, branco;

int main () {
	int n, m, x, y;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	while (cin >> n >> m)
	{
		preto.clear();
		branco.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			preto.pb(pv(x, y));
		}
		for (int i = 0; i < m; i++)
		{
			cin >> x >> y;
			branco.pb(pv(x, y));
		}
		
		int ans=0;
		int cnt;
		for (int i = 0; i < n-2; i++)
		{
			for (int j = i+1; j < n-1; j++)
			{
				for (int k = j+1; k < n; k++)
				{
					cnt=0;
					//~ printf("%d %d %d\n", i, j, k);
					for (int l = 0; l < m; l++)
					{
						if(contido(preto[i], preto[j], preto[k], branco[l])){
							//~ printf("%d, %d contido\n", branco[l].x, branco[l].y);
							cnt++;
						}
					}
					//~ cout << cnt << endl;
					ans += (cnt*cnt);
				}
			}
		}
		cout << ans << "\n";
		
	}
	
	
	return 0;
}
