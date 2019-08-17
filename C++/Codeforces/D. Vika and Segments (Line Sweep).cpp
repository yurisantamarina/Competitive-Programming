#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;

#define MAXN 200100
#define ABRE 1
#define VERTICAL 2
#define FECHA 3

struct pv{
	ll x, y;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv aa, pv bb){
		a = aa;
		b = bb;
	}
};

struct event{
	int x, y, y0, tipo;
	event(){}
	event(int a, int b, int c, int d){
		x = a;
		y = b;
		y0 = c;
		tipo = d;
	}
	event(int a, int b, int c){
		x = a;
		y = b;
		tipo = c;
	}
	
	bool operator < (event other) const{
		if(x == other.x) return tipo < other.tipo;
		return x < other.x;
	}
};

vector<seg> horizontal, vertical;
map<ll, int> mapa;
int bit[MAXN];
vector<event> evento;

bool compareHorizontal(seg &r, seg &s){
	if(r.a.y == s.a.y){
		if(r.a.x == s.a.x) return r.b.x < s.b.x;
		return r.a.x < s.a.x;
	}else{
		return r.a.y < s.a.y;
	}
}

bool compareVertical(seg &r, seg &s){
	if(r.a.x == s.a.x){
		if(r.a.y == s.a.y) return r.b.y < s.b.y;
		return r.a.y < s.a.y;
	}else{
		return r.a.x < s.a.x;
	}
}

void update(int pos, int val){
	while (pos < MAXN)
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
	return sum(r) - sum(l-1);
}

int getQtd(){
	int ans = 0;
	for (int i = 0; i < (int)evento.size(); i++)
	{
		if(evento[i].tipo == ABRE){
			update(mapa[evento[i].y], 1);
		}else if(evento[i].tipo == FECHA){
			update(mapa[evento[i].y], -1);
		}else{
			ans += query(mapa[evento[i].y], mapa[evento[i].y0]);
		}
		
	}
	return ans;
}


int main () {
	int n;
	ll x1, y1, x2, y2;
	cin >> n;
	
	set<ll> s;
	
	for (int i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		s.insert(x1);
		s.insert(y1);
		s.insert(x2);
		s.insert(y2);
		
		if(y1 == y2){
			if(x1 > x2) swap(x1, x2);
			horizontal.pb(seg(pv(x1, y1), pv(x2, y2)));
		}else{
			if(y1 > y2) swap(y1, y2);
			vertical.pb(seg(pv(x1, y1), pv(x2, y2)));
		}
	}
	
	int idx = 2;
	for(auto i : s){
		mapa[i] = idx++;
	}
	
	if(horizontal.size() > 0) sort(horizontal.begin(), horizontal.end(), compareHorizontal);
	if(vertical.size() > 0) sort(vertical.begin(), vertical.end(), compareVertical);
	
	
	ll x, y;
	ll atL, atR;
	
	ll total = 0LL;
	
	
	for (int i = 0; i < (int)horizontal.size(); i++)
	{
		if(i==0){
			y = horizontal[i].a.y;
			atL = horizontal[i].a.x;
			atR = horizontal[i].b.x;
		}else{
			if(horizontal[i].a.y == y){
				if(horizontal[i].a.x <= atR){
					atR = max(atR, horizontal[i].b.x);
				}else{
					evento.pb(event(atL, y, ABRE));
					evento.pb(event(atR, y, FECHA));
					total += (atR - atL+1);
					atL = horizontal[i].a.x;
					atR = horizontal[i].b.x;
				}
			}else{
				evento.pb(event(atL, y, ABRE));
				evento.pb(event(atR, y, FECHA));
				total += (atR - atL+1);
				y = horizontal[i].a.y;
				atL = horizontal[i].a.x;
				atR = horizontal[i].b.x;
			}
		}
	}
	if(horizontal.size()>0){
		evento.pb(event(atL, y, ABRE));
		evento.pb(event(atR, y, FECHA));
		total += (atR - atL+1);
	}
	
	for (int i = 0; i < vertical.size(); i++)
	{
		if(i==0){
			x = vertical[i].a.x;
			atL = vertical[i].a.y;
			atR = vertical[i].b.y;
		}else{
			if(vertical[i].a.x == x){
				if(vertical[i].a.y <= atR){
					atR = max(atR, vertical[i].b.y);
				}else{
					evento.pb(event(x, atL, atR, VERTICAL));
					total += (atR - atL+1);
					atL = vertical[i].a.y;
					atR = vertical[i].b.y;
				}
			}else{
				evento.pb(event(x, atL, atR, VERTICAL));
				total += (atR - atL+1);
				x = vertical[i].a.x;
				atL = vertical[i].a.y;
				atR = vertical[i].b.y;
			}
		}
	}
	if(vertical.size()>0){
		evento.pb(event(x, atL, atR, VERTICAL));
		total += (atR - atL+1);
	}
	
	sort(evento.begin(), evento.end());
	int qtdInter = getQtd();
	cout << total - qtdInter << "\n";
	
	
	
	return 0;
}
