#include <bits/stdc++.h>

using namespace std;
#define MAXN 210101
#define INF 1000000000000000LL
#define F first
#define S second
typedef long long int ll;

set<ll> vessel;
ll n, vol[MAXN], at[MAXN];

void add(ll id, ll qtd){
	if(at[id] + qtd <= vol[id]){
		at[id] += qtd;
		return;
	}
	
	ll falta = qtd;
	set<ll>::iterator it = vessel.lower_bound(id);
	vector<ll> aux;
	
	while (falta > 0 && it != vessel.end())
	{
		id = *it;
		if(at[id] + falta <= vol[id]){
			at[id] += falta;
			return;
		}
		falta -= (vol[id] - at[id]);
		at[id] = vol[id];
		it = vessel.erase(it);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> vol[i];
		vessel.insert(i);
	}
	vol[n+1] = INF;
	vessel.insert(n+1);
	
	ll q, op, pos, qtd;
	cin >> q;
	while (q--)
	{
		cin >> op;
		if(op == 1){
			cin >> pos >> qtd;
			add(pos, qtd);
		}else{
			cin >> pos;
			cout << at[pos] << "\n";
		}
	}
	
	
	
	return 0;
}
