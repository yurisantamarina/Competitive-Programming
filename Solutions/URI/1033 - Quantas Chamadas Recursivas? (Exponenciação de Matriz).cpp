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
ll MOD;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

vector<ll> ans;
void convert (ll n, ll base)
{
	if (n >= base)
		convert ((n / base), base);

	int c = n % base;
	
	if (c > 9)
		ans.pb (int(c));

	else
		ans.pb (int(c));
}

struct mat{
	ll v[3][3];
	//~ mat(){}
	//~ mat()
	const mat operator * (mat a){
		mat b;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				b.v[i][j] = 0LL;
				for (int k = 0; k < 3; k++)
				{
					b.v[i][j] = (b.v[i][j] + (v[i][k] * a.v[k][j])%MOD)%MOD;
				}
			}
		}
		
		return b;
	}
};

mat base, ret;

void preenche(){
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(i==0) base.v[i][j] = 1;
			else if(i==1 && j==0) base.v[i][j] = 1;
			else if(i==2 && j==2) base.v[i][j] = 1;
			else base.v[i][j] = 0;
			
			ret.v[i][j] = (i==j);
		}
	}
}

mat exponencia(int exp){
	if(exp==0) return ret;
	
	mat aux = exponencia(exp / 2);
	aux = aux * aux;
	if(exp%2 != 0) aux = aux * base;
	
	return aux;
}

int main () {
	preenche();
	ll n, b, caso=1;
	while (cin >> n >> b)
	{
		if(!n && !b) break;
		MOD = b;
		mat aux = exponencia(n-1 >= 0 ? n-1 : n);
	
		//~ for (int i = 0; i < 3; i++)
		//~ {
			//~ for (int j = 0; j < 3; j++)
			//~ {
				//~ cout << aux.v[i][j] << " ";
			//~ }
			//~ cout << endl;
			
		//~ }
		
		convert(aux.v[0][0] + aux.v[0][1] + aux.v[0][2], b);
		//~ for (int i = 0; i < ans.size(); i++)
		//~ {
			//~ cout << ans[i] << " ";
		//~ }
		//~ cout << endl;
		
		cout << "Case " << caso++ << ": " << n << " " << b << " " << ans[ans.size()-1] << "\n";
	}
	
	
	//~ for (int i = 0; i <= 5; i++)
	//~ {
		
		
	//~ }
	
	

	
	
	
	return 0;
}
