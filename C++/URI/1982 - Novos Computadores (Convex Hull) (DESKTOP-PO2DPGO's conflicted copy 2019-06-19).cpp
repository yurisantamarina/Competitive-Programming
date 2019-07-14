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
	
	bool operator < (pv other) const{
		if(x==other.x) return y < other.y;
		return x < other.x;
	}
};

int cross(pv a, pv b){
	return a.x*b.y - a.y*b.x;
}

vector<pv> ponto;

vector<pv> pilhaUpper(100000);
vector<pv> pilhaLower(100000);
int szUpper, szLower;
double ans;

double dist(pv a, pv b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void build(){
	szUpper = 0;
	szLower = 0;
	pv a, b, c;
	
	for (int i = 0; i < ponto.size(); i++)
	{
		if(szUpper <= 1) pilhaUpper[szUpper++] = ponto[i];
		else{
			a = pilhaUpper[szUpper-2];
			b = pilhaUpper[szUpper-1];
			c = ponto[i];
			
			while (szUpper > 1 && cross(b-a, c-b) > 0)
			{
				szUpper--;
				a = pilhaUpper[szUpper-2];
				b = pilhaUpper[szUpper-1];
			}
			pilhaUpper[szUpper++] = c;
		}
		
		
		if(szLower <= 1) pilhaLower[szLower++] = ponto[i];
		else{
			a = pilhaLower[szLower-2];
			b = pilhaLower[szLower-1];
			c = ponto[i];
			
			while (szLower > 1 && cross(b-a, c-b) < 0)
			{
				szLower--;
				a = pilhaLower[szLower-2];
				b = pilhaLower[szLower-1];
			}
			pilhaLower[szLower++] = c;
		}
	}
	
	for (int i = 0; i < szUpper-1; i++)
	{
		ans += dist(pilhaUpper[i], pilhaUpper[i+1]);
	}
	
	for (int i = 0; i < szLower-1; i++)
	{
		ans += dist(pilhaLower[i], pilhaLower[i+1]);
	}
}

void reset(){
	ans = 0.0;
	ponto.clear();
}

int main () {
	int n, x, y;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	while (cin >> n, n)
	{
		reset();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			ponto.pb(pv(x, y));
		}
		
		sort(ponto.begin(), ponto.end());
		
		build();
		
		cout << fixed << setprecision(2) << "Tera que comprar uma fita de tamanho " << ans << ".\n";
	}
	
	
	
	
	return 0;
}
