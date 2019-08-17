#include <bits/stdc++.h>

using namespace std;
#define MAXN 301010
#define pb push_back
typedef long long int ll;

struct node{
	node *nxt[2];
	ll c;
	node(){
		nxt[0] = NULL;
		nxt[1] = NULL;
	}
};

node * clona(node *t){
	node* n = new node();
	
	n->nxt[0] = t->nxt[0];
	n->nxt[1] = t->nxt[1];
	n->c = t->c;
	
	return n;
}

node *root[MAXN];
vector<ll> g[MAXN];
ll key[MAXN];
map<ll, ll> mapa;
int idx = 1;

node * update(node *t, string s){
	node *novo = clona(t);
	node *ans = novo;
	node *tmp;
	
	ll c;
	for (ll i = 0; i < (ll)s.size(); i++)
	{
		c = s[i]-'0';
		
		if(novo->nxt[c]){
			tmp = clona(novo->nxt[c]);
			novo->nxt[c] = tmp;
		}else{
			tmp = new node();
			tmp->c = c;
			novo->nxt[c] = tmp;
		}
		novo = novo->nxt[c];
	}
	
	
	return ans;
}

string change(ll val){
	bitset<34> b(val);
	return b.to_string();
}

void dfs(ll u, ll pai){
	root[u] = update(root[pai], change(key[u]));
	for(ll v : g[u])
		dfs(v, u);
}

ll queryMin(node *tmp, string s){
	node *t = tmp;
	ll c;
	ll ans = 0;
	
	for (ll i = 0; i < (ll)s.size(); i++)
	{
		c = s[i]-'0';
		if(t->nxt[c]){
			t = t->nxt[c];
		}else{
			ans |= (1LL<<(33 - i));
			t = t->nxt[!c];
		}
	}
	return ans;
}

ll queryMax(node *tmp, string s){
	node *t = tmp;
	ll c;
	ll ans = 0;
	
	for (ll i = 0; i < (ll)s.size(); i++)
	{
		c = s[i]-'0';
		if(t->nxt[!c]){
			t = t->nxt[!c];
			ans |= (1LL<<(33 - i));
		}else{
			t = t->nxt[c];
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll n, q, u, v, k, fst;
	root[0] = new node();
	
	cin >> n >> q;
	cin >> fst >> k;
	if(!mapa.count(fst)) mapa[fst] = idx++;
	fst = mapa[fst];
	
	key[fst] = k;
	
	for (ll i = 0; i < n-1; i++)
	{
		cin >> u >> v >> k;
		if(!mapa.count(u)) mapa[u] = idx++;
		if(!mapa.count(v)) mapa[v] = idx++;
		u = mapa[u];
		v = mapa[v];
		key[u] = k;
		g[v].pb(u);
	}
	
	dfs(fst, 0);
	
	string s;
	ll op;
	ll lst = 0, a, b;
	for (ll i = 0; i < q; i++)
	{
		cin >> op;
		op ^= lst;
		
		if(op == 0){
			cin >> v >> u >> k;
			v ^= lst;
			u ^= lst;
			k ^= lst;
			if(!mapa.count(u)) mapa[u] = idx++;
			if(!mapa.count(v)) mapa[v] = idx++;
			
			u = mapa[u];
			v = mapa[v];
			
			
			root[u] = update(root[v], change(k));
		}else{
			cin >> v >> k;
			v ^= lst;
			k ^= lst;
			if(!mapa.count(v)) mapa[v] = idx++;
			
			v = mapa[v];
			
			s = change(k);
			a = queryMin(root[v], s);
			b = queryMax(root[v], s);
			cout << a << " " << b << "\n";
			lst = a ^ b;
		}
	}
	
	
	return 0;
}
