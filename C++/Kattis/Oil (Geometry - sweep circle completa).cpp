#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define ABRE 0
#define FECHA 1
typedef long long int ll;

struct pv{
	ll x, y;
	pv(){}
	pv(ll _x, ll _y){
		x = _x;
		y = _y;
	}
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
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

struct event{
	pv p;
	int tipo;
	ll val;
	event(){}
	event(pv _p, int _tipo, ll _val){
		p = _p;
		tipo = _tipo;
		val = _val;
	}
};

vector<event> evt;
vector<seg> deposit;

ll cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

int getQuad(pv a){
	if(a.x >= 0 && a.y >= 0) return 1;
	if(a.x < 0 && a.y > 0) return 2;
	if(a.x < 0 && a.y <= 0) return 3;
	return 4;
} 

bool comparePolarAngle(event A, event B){
	pv a = A.p;
	pv b = B.p;
	int q1 = getQuad(a);
	int q2 = getQuad(b);
	if(q1 != q2) return q1 < q2;
	
	ll c = cross(a, b);
	if(c > 0){
		return true;
	}else if(c < 0){
		return false;
	}else{
		return A.tipo < B.tipo;
	}
}

void build(int idx, int op){
	evt.clear();
	vector<event> aux;
	pv origin = op == 0 ? deposit[idx].a : deposit[idx].b;
	pv at;
	
	for (int i = 0; i < (int)deposit.size(); i++)
	{
		if(deposit[i].a.y == origin.y) continue;
		if(deposit[i].a.y < origin.y){
			at = deposit[i].a - origin;
			aux.pb(event(at, ABRE, deposit[i].b.x - deposit[i].a.x));
			at = deposit[i].b - origin;
			aux.pb(event(at, FECHA, deposit[i].b.x - deposit[i].a.x));
		}else{
			at = deposit[i].b - origin;
			aux.pb(event(at, ABRE, deposit[i].b.x - deposit[i].a.x));
			at = deposit[i].a - origin;
			aux.pb(event(at, FECHA, deposit[i].b.x - deposit[i].a.x));
		}
	}
	sort(aux.begin(), aux.end(), comparePolarAngle);
	
	vector<event> cima, baixo;
	for (int i = 0; i < (int)aux.size(); i++)
	{
		if(aux[i].p.y < 0){
			baixo.pb(aux[i]);
		}else{
			cima.pb(aux[i]);
		}
	}
	
	int i = 0, sz1 = (int)cima.size(), j = 0, sz2 = (int)baixo.size();
	
	ll c;
	while (i < sz1 && j < sz2)
	{
		c = cross(cima[i].p, baixo[j].p);
		if(c < 0){
			evt.pb(cima[i++]);
		}else if(c > 0){
			evt.pb(baixo[j++]);
		}else{
			if(cima[i].tipo < baixo[j].tipo){
				evt.pb(cima[i++]);
			}else{
				evt.pb(baixo[j++]);
			}
		}
	}
	while (i < sz1)
	{
		evt.pb(cima[i++]);
	}
	
	while (j < sz2)
	{
		evt.pb(baixo[j++]);
	}
}

ll sweep(){
	ll ans = 0, at = 0;
	for (int i = 0; i < (int)evt.size(); i++)
	{
		if(evt[i].tipo == ABRE){
			at += evt[i].val;
			//~ printf("somando %d\n", evt[i].val);
		}else{
			at -= evt[i].val;
			//~ printf("subtraindo %d\n", evt[i].val);
		}
		ans = max(ans, at);
	}
	return ans;
}

int main(){
	int n;
	ll x1, x2, y;
	ll ans = 0LL, cost;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x1 >> x2 >> y;
		if(x1 > x2) swap(x1, x2);
		deposit.pb(seg(pv(x1, -y), pv(x2, -y)));
	}
	
	for (int i = 0; i < n; i++)
	{
		cost = deposit[i].b.x - deposit[i].a.x; 
		build(i, 0);
		ans = max(ans, sweep() + cost);
		build(i, 1);
		ans = max(ans, sweep() + cost);
	}
	cout << ans << "\n";
	
	
	return 0;
}
