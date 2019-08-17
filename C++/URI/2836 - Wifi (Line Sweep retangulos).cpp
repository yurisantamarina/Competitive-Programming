#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
#define ABRE 0
#define FECHA 1

struct event{
	int x, y1, y2, type, id;
	event(){}
	event(int a, int b, int c, int d, int e){
		x = a;
		y1 = b;
		y2 = c;
		type = d;
		id = e;
	}
	bool operator < (event other) const{
		return x < other.x;
	}
};

vector<event> eve;
int ylo[MAXN], yhi[MAXN];
set<pair<int, pair<int, int> > > atv;
bool fechei[MAXN];

int lineSweep(){
	sort(eve.begin(), eve.end());
	int ans = 0;
	
	for(event &e : eve){
		if(e.type == ABRE){
			atv.insert({e.y1, {ABRE, e.id}});
			atv.insert({e.y2, {FECHA, e.id}});
		}else{
			if(!fechei[e.id])
				ans++;
			
			auto it = atv.upper_bound({e.y2, {1e9 + 5, 1e9 + 5}});
			if(it != atv.end() && it->S.F == FECHA){//se o segmento acima for FECHA, o retangulo atual deve fechar o retangulo acima, se for ABRE, tem algum retangulo acima de mim que vai fechar oq eu to querendo fechar, entao nao preciso me preocupar
				int id = it->S.S;
				fechei[id] = true;
				atv.erase({yhi[id], {FECHA, id}});
				atv.erase({ylo[id], {ABRE, id}});
			}
			
			fechei[e.id] = true;
			if(atv.count({e.y1, {ABRE, e.id}})){//apaga meus segmentos
				atv.erase({e.y1, {ABRE, e.id}});
				atv.erase({e.y2, {FECHA, e.id}});
			}
		}
	}
	
	return ans;
}

int main(){
	int n, x1, y1, x2, y2;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		eve.push_back(event(x1, y2, y1, ABRE, i));
		eve.push_back(event(x2, y2, y1, FECHA, i));
		yhi[i] = y1;
		ylo[i] = y2;
	}
	
	printf("%d\n", lineSweep());
	
	return 0;
}
