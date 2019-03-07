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

#define MAXN 200010

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
};

struct event{
	ll x, y;
	int id;
	event(){}
	event(ll a, ll b, int c){
		x = a;
		y = b;
		id = c;
	}
	
	bool operator < (event other) const {
		if(x==other.x) return y < other.y;
		return x < other.x;
	}
};

struct resp{
	int NO, SO, SE, NE;
	resp(){}
};

vector<event> v;
map<ll, int> mapa;
resp saida[MAXN/2];
int bit[MAXN];
vector<pv> ponto;

void update(int pos, int val){
	while (pos < MAXN)
	{
		bit[pos] += val;
		pos += pos & (-pos);
	}
}

int query(int pos){
	int ans = 0;
	while (pos > 0)
	{
		ans += bit[pos];
		pos -= pos & (-pos);
	}
	return ans;
}

void sweep1(){
	queue<int> q1, q2;
	int at = -1;
	for (int i = 0; i < v.size(); i++)
	{
		
		if(v[i].x != at){
			at = v[i].x;
			while (!q1.empty())
			{
				update(ponto[q1.front()].y, 1);
				q1.pop();
			}
			while (!q2.empty())
			{
				saida[q2.front()].NO = query(MAXN-10) - query(ponto[q2.front()].y);
				q2.pop();
			}
			q1.push(v[i].id);
			q2.push(v[i].id);
			
			saida[v[i].id].SO = query(v[i].y);
		}else{
			q1.push(v[i].id);
			q2.push(v[i].id);
			saida[v[i].id].SO = query(v[i].y);
		}
	}
	while (!q1.empty())
	{
		update(ponto[q1.front()].y, 1);
		q1.pop();
	}
	while (!q2.empty())
	{
		saida[q2.front()].NO = query(MAXN-1) - query(ponto[q2.front()].y);
		q2.pop();
	}
}

void sweep2(){
	memset(bit, 0, sizeof bit);
	queue<int> q1, q2;
	int at = -1;
	for (int i = 0; i < v.size(); i++)
	{
		
		if(v[i].x != at){
			at = v[i].x;
			while (!q1.empty())
			{
				update(ponto[q1.front()].y, 1);
				q1.pop();
			}
			while (!q2.empty())
			{
				saida[q2.front()].SE = query(ponto[q2.front()].y-1);
				q2.pop();
			}
			q1.push(v[i].id);
			q2.push(v[i].id);
			
			saida[v[i].id].NE = query(MAXN-10) - query(v[i].y-1);
		}else{
			q1.push(v[i].id);
			q2.push(v[i].id);
			saida[v[i].id].NE = query(MAXN-10) - query(v[i].y-1);
		}
	}
	while (!q1.empty())
	{
		update(ponto[q1.front()].y, 1);
		q1.pop();
	}
	while (!q2.empty())
	{
		saida[q2.front()].SE = query(ponto[q2.front()].y-1);
		q2.pop();
	}
}

int main () {
	int n;
	ll x, y;
	cin >> n;
	set<ll> s;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		ponto.pb(pv(x, y));
		v.pb(event(x, y, i));
		s.insert(x);
		s.insert(y);
	}
	
	int idx = 2;
	for (auto i : s)
	{
		mapa[i] = idx++;
	}
	
	for (int i = 0; i < n; i++)
	{
		ponto[i].x = mapa[ponto[i].x];
		ponto[i].y = mapa[ponto[i].y];
		v[i].x = ponto[i].x;
		v[i].y = ponto[i].y;
	}
	
	
	sort(v.begin(), v.end());
	
	sweep1();
	reverse(v.begin(), v.end());
	sweep2();
	
	for (int i = 0; i < n; i++)
	{
		cout << saida[i].NO << " " << saida[i].SO << " " << saida[i].SE << " " << saida[i].NE << "\n";
	}
	
	
	return 0;
}
