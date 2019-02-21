#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define MAXN 101010
#define pb push_back
#define mp make_pair
#define oioi printf("oioi\n")
typedef long long int ll;

int read_int(){
	char r;
	bool start=false,neg=false;
	int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}


struct reta{
	int a, b, id;
	reta(){}
	reta(int _a, int _b, int _id){
		a = _a;
		b = _b;
		id = _id;
	}
};

double inf = 1000000000000000000.0;
reta ch[2][MAXN];
int tam[2];
int n;
vector<reta> hab, can;
vector<reta> habAux, canAux;

bool remove(reta _1, reta _2, reta _3){
	bool ans;
	ans = (_3.b - _1.b) *1LL* (_1.a - _2.a) <= (_2.b - _1.b) *1LL* (_1.a - _3.a);
	return ans;
}

void add(reta a, int op){
	int sz = tam[op];
	
	while (sz > 1 && remove(ch[op][sz-2], ch[op][sz-1], a))
	{
		sz--;
	}
	ch[op][sz++] = a;
	tam[op] = sz;
}

bool compareHab(reta _1, reta _2){
	if(_1.a == _2.a){//mesma inclinacao
		return _1.b > _2.b;//maior habilidade
	}
	
	return _1.a < _2.a;//como habilidade é CH de máximo, a ordenação tem que ser crescente no slope
}

bool compareCan(reta _1, reta _2){
	if(_1.a == _2.a){
		return _1.b < _2.b;
	}
	return _1.a > _2.a;
}

void tiraRepetido(){
	hab.pb(habAux[0]);
	for (int i = 1; i < habAux.size(); i++)
	{
		if(habAux[i].a != hab[hab.size()-1].a)
			hab.pb(habAux[i]);
	}
	
	can.pb(canAux[0]);
	for (int i = 1; i < canAux.size(); i++)
	{
		if(canAux[i].a != can[can.size()-1].a)
			can.pb(canAux[i]);
	}
}

double getInter(reta _1, reta _2){
	return (_2.b - _1.b)*1.0 / (_1.a - _2.a);
}

pair<double, double> inter[2][MAXN];

void build(int op){
	reta aux = ch[op][0];
	
	inter[op][aux.id].F = 0.0;
	//~ if(tam[op]==1){
		//~ inter[op][aux.id] = mp(-inf, inf);
		//~ return;
	//~ }
	
	reta a, b;
	double x;
	//~ printf("tam[%d] = %d\n", op, tam[op]);
	for (int i = 0; i < tam[op]-1; i++)
	{
		a = ch[op][i];
		b = ch[op][i+1];
		x = getInter(a, b);
		//~ x = 1.0;
		//~ printf("%.5lf ", x);
		if(x < 0) x = 0.0;
		inter[op][a.id].S = x;
		inter[op][b.id].F = x;
		
	}
	//~ printf("\n");
	//~ oioi;
	if(tam[op]==1)
		inter[op][aux.id].S = inf;
	else
		inter[op][b.id].S = inf;
}

bool ok(pair<double, double> a, pair<double, double> b){
	//~ pair<double, double> a, b;
	//~ printf("a.F = %.2lf   a.S = %.2lf\n", a.F, a.S);
	//~ printf("b.F = %.2lf   b.S = %.2lf\n", b.F, b.S);
	if(a.F < 0 && a.S < 0) return false;
	if(b.F < 0 && b.S < 0) return false;
	if(a.F==a.S || b.F==b.S) return false;
	
	if(a.F == b.F){
		if(a.S > b.S) swap(a, b);
	}else if(a.F < b.F){
		
	}else{
		swap(a, b);
	}
	
	
	return b.F < a.S;
}

int main(){
	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	//~ cin >> n;
	n = read_int();
	int habIni, habTx, canIni, canTx;
	for (int i = 0; i < n; i++)
	{
		//~ cin >> habIni >> habTx >> canIni >> canTx;
		habIni = read_int();
		habTx = read_int();
		canIni = read_int();
		canTx = read_int();
		habAux.pb(reta(habTx, habIni, i));
		canAux.pb(reta(canTx, canIni, i));
	}
	sort(habAux.begin(), habAux.end(), compareHab);
	sort(canAux.begin(), canAux.end(), compareCan);
	tiraRepetido();
	
	
	for (int i = 0; i < hab.size(); i++)
	{
		add(hab[i], 0);
	}
	for (int i = 0; i < can.size(); i++)
	{
		add(can[i], 1);
	}
	
	//~ printf("\n\nhabAux: \n");
	//~ for (ll i = 0; i < habAux.size(); i++)
	//~ {
		//~ printf("y%d = %dx + %d\n", habAux[i].id, habAux[i].a, habAux[i].b);
	//~ }
	
	//~ printf("\ncanAux: \n");
	//~ for (ll i = 0; i < canAux.size(); i++)
	//~ {
		//~ printf("y%d = %dx + %d\n", canAux[i].id, canAux[i].a, canAux[i].b);
	//~ }
	
	//~ printf("\nhab: \n");
	//~ for (ll i = 0; i < hab.size(); i++)
	//~ {
		//~ printf("y%d = %dx + %d\n", hab[i].id, hab[i].a, hab[i].b);
	//~ }
	
	//~ printf("\ncan: \n");
	//~ for (ll i = 0; i < can.size(); i++)
	//~ {
		//~ printf("y%d = %dx + %d\n", can[i].id, can[i].a, can[i].b);
	//~ }
	
	
	//~ printf("\n\nCH hab:\n");
	//~ for (ll i = 0; i < tam[0]; i++)
	//~ {
		//~ printf("y%d = %dx + %d\n", ch[0][i].id, ch[0][i].a, ch[0][i].b);
	//~ }
	//~ printf("\nCH can:\n");
	//~ for (ll i = 0; i < tam[1]; i++)
	//~ {
		//~ printf("y%d = %dx + %d\n", ch[1][i].id, ch[1][i].a, ch[1][i].b);
	//~ }
	
	for (int i = 0; i < n; i++)
	{
		inter[0][i] = mp(-1, -1);
		inter[1][i] = mp(-1, -1);
	}
	
	build(0);//hab
	build(1);//can
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		//~ printf("\nid = %d  [%.5lf, %.5lf]\n", i, inter[0][i].F, inter[0][i].S);
		//~ printf("id = %d  [%.5lf, %.5lf]\n", i, inter[1][i].F, inter[1][i].S);
		ans += ok(inter[0][i], inter[1][i]);
	}
	
	printf("%d\n", ans);
	//~ cout << ans << "\n";
	
	
	return 0;
}
