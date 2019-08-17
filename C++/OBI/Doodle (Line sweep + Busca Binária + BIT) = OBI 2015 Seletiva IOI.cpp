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

struct event{
	ll x, y, y0, tipo;
	event(){}
	event(ll a, ll b, ll c, ll d){
		x = a;
		y = b;
		y0 = c;
		tipo = d;
	}
	event(ll a, ll b, ll c){
		x = a;
		y = b;
		y0 = 0;
		tipo = c;
	}
	
	bool operator < (event other) const{
		if(x==other.x) return tipo < other.tipo;
		return x < other.x;
	}
};

map<ll, ll> mapa;
map<ll, ll> rev;
ll abre = 1;
ll vertical = 2;
ll fecha = 3;
vector<event> v;
vector<event> v2;
int tam[1010101];
int bit[101010];

void update(int pos, int val){
	while (pos < 101010)
	{
		bit[pos] += val;
		pos += pos & (-pos);
	}
}

int sum(int pos){
	int ans = 0;
	while (pos > 0)
	{
		ans += bit[pos];
		pos -= pos & (-pos);
	}
	return ans;
}

int query(int l, int r){
	if(l > r) return 0;
	return sum(r) - sum(l-1);
}

int inters(int sz){
	int ans = 0;
	for (int i = 0; i < sz; i++)
	{
		if(v[i].tipo == abre){
			update(v[i].y, 1);
		}else if(v[i].tipo == fecha){
			update(v[i].y, -1);
		}else{
			ans += query(v[i].y+1, v[i].y0-1);
		}
	}
	return ans;
}

int main () {
	int xLast = 0, yLast = 0;
	int x=0, y=0;
	int desloc;
	int n, k;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	set<int> s;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> desloc;
		if(i%2==0){
			x += desloc;
		}else{
			y += desloc;
		}
		
		s.insert(xLast);
		s.insert(yLast);
		s.insert(x);
		s.insert(y);
		
		if(x==xLast){//vertical
			v.pb(event(x, min(y, yLast), max(y, yLast), vertical));
		}else{
			if(xLast < x){
				v.pb(event(xLast, yLast, abre));
				v.pb(event(x, y, fecha));
			}else{
				v.pb(event(xLast, yLast, fecha));
				v.pb(event(x, y, abre));
			}
		}
		tam[i+1] = v.size();
		xLast = x;
		yLast = y;
	}
	
	int idx = 1;
	for(auto i : s){
		mapa[i] = idx++;
		rev[idx-1] = i;
	}
	
	for (int i = 0; i < v.size(); i++)
	{
		v[i].x = mapa[v[i].x];
		v[i].y = mapa[v[i].y];
		if(v[i].tipo == vertical)
			v[i].y0 = mapa[v[i].y0];
	}	
	
	int lo = 1;
	int hi = n;
	int mid;
	int qtd;
	int ans1 = 0;
	int ans2 = 0;
	int ans3 = 0;
	int ans4 = 0;
	v2 = v;
	
	int cnt = 0;
	while (cnt++ < 20)
	{
		mid = (lo+hi)/2;
		v = v2;
		sort(v.begin(), v.begin()+tam[mid]);
		qtd = inters(tam[mid]);
		
		if(qtd <= k){
			ans1 = mid;
			ans2 = qtd;
			lo = mid+1;
		}else{
			ans3 = mid;
			ans4 = qtd;
			hi = mid-1;
		}
	}
	
	if(ans3==0 && ans4==0)
		cout << ans1 << " " << ans2 << "\n";
	else
		cout << ans3 << " " << ans4 << "\n";
	
	
	
	return 0;
}
