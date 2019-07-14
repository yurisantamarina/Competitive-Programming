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
	pv(int _x, int _y){
		x = _x;
		y = _y;
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};

vector<seg> segmento;

pv toVec(pv a, pv b){
	return b-a;
}

int cross(pv a, pv b){
	int c = a.x*b.y - a.y*b.x;
	if(c > 0) return 1;
	if(c < 0) return -1;
	return 0;
}

double dist(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

bool inter(seg r, seg s){
	pv a, b, c, d;
	a = r.a;
	b = r.b;
	c = s.a;
	d = s.b;
	
	//~ printf("a = (%d, %d)\n", a.x, a.y);
	//~ printf("b = (%d, %d)\n", b.x, b.y);
	//~ printf("c = (%d, %d)\n", c.x, c.y);
	//~ printf("d = (%d, %d)\n", d.x, d.y);
	
	int c1, c2, c3, c4;
	c1 = cross(toVec(a, b), toVec(a, d));
	c2 = cross(toVec(a, b), toVec(a, c));
	c3 = cross(toVec(c, d), toVec(c, a));
	c4 = cross(toVec(c, d), toVec(c, b));
	
	//~ printf("%d %d %d %d\n", c1, c2, c3, c4);
	
	if(c1!=c2 && c3!=c4) return true;
	
	double tam1, tam2;
	tam1 = dist(a, b);
	tam2 = dist(c, d);
	if(!c1 && !c2 && !c3 && !c4){
		if(dist(a, c) <= tam1+tam2 && dist(a, d) <= tam1+tam2 && dist(b, c) <= tam1+tam2 && dist(b, d) <= tam1+tam2){
			return true;
		}
	}
	
	return false;
}

int main () {
	int tc, x, y, n, x0, y0;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		segmento.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> x0 >> y0;
			segmento.pb(seg(pv(x, y), pv(x0, y0)));
		}
		
		int ans = 0;
		bool ok=true;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if(i==j) continue;
				if(inter(segmento[i], segmento[j])){
					//~ printf("(%d, %d)-(%d, %d)    (%d, %d)-(%d, %d)\n", segmento[i].a.x, segmento[i].a.y, segmento[i].b.x, segmento[i].b.y, segmento[j].a.x, segmento[j].a.y, segmento[j].b.x, segmento[j].b.y);
					ok = false;
					//~ printf("ok = %s\n", ok ? "true" : "false");
				}
			}
			//~ cout << endl;
			ans += (ok==true ? 1 : 0);
			ok = true;
		}
		cout << ans << "\n";
	}
	
	
	return 0;
}
