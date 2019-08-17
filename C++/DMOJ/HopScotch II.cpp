#include <bits/stdc++.h>

using namespace std;
#define MAXN 8388608
typedef long long int ll;

int N, K;

struct state{
	ll mn;
	int st, idx;
	state(){}
	state(ll _mn, int _st, int _idx){
		mn = _mn;
		st = _st;
		idx = _idx;
	}
	bool operator == (state &other){
		return mn == other.mn && st == other.st && idx == other.idx;
	}
};

vector<state> v;
stack<ll> inp;
vector<int> par;
int ini, fim;
queue<state> dp;

state query(){
	return v[ini];
}
bool can_pop(state &a, state &b){
	if(a.mn < b.mn) return false;
	if(a.mn > b.mn) return true;
	if(a.st > b.st) return false;
	if(a.st < b.st) return true;
	return a.idx < b.idx;
}
void push(state e){
	while(fim > 0 && ini < fim && can_pop(v[fim - 1], e)) fim--;
	v[fim++] = e;
}
void pop(state e){
	if(ini == fim) return;
	if(v[ini] == e) ini++;
}

int main(){
	//~ cout << "oi\n";
	//~ return 0;
	scanf("%d %d", &N, &K);
	//~ return 0;
	inp.push(0);
	par.resize(N + 3);
	v.resize(N + 3);
	ll x;
	for(int i = 1; i <= N; i++){
		scanf("%lld", &x);
		inp.push(x);
	}
	
	
	//~ return 0;
	push(state(0, 0, N + 1));
	
	state best, tmp;
	dp.push(state(0, 0, N + 1));
	for(int i = N; i >= 0; i--){
		best = query();
		tmp = state(best.mn + inp.top(), best.st + 1, i);
		inp.pop();
		
		//~ cout << "sz = " << dp.size() << endl;
		if(i + K <= N + 1){
			pop(dp.front());
			dp.pop();
		}
		par[i] = best.idx;
		push(tmp);
		dp.push(tmp);
	}
	printf("%lld\n", tmp.mn);
	
	bool fst = true;
	int at = 0;
	while(at != N + 1){
		at = par[at];
		if(at == N + 1) break;
		if(!fst) printf(" ");
		fst = false;
		printf("%d", at);
	}
	printf("\n");
	
	return 0;
}
