#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define MAXN 101010
#define INF 1e8
#define BITMAX 17
#define F first
#define S second
#define mp make_pair

struct node{
	node *nxt[2];
	int mn;
	node(){
		nxt[0] = nxt[1] = 0;
		mn = INF;
	}
};

typedef node* trie;

trie root[MAXN];
int x, k, s;
int counter = 0;
map<pair<pair<int, int>, int>, pair<int, int> > memo;

void add(int val, int idx){
	trie t = root[idx];
	//~ printf("inserindo %d em %d\n", val, idx);
	int c;
	for (int i = BITMAX; i >= 0; i--)
	{
		c = (val & (1 << i)) != 0;
		//~ printf("%d", c);
		if(!t->nxt[c]){
			t->nxt[c] = new node();
		}
		t = t->nxt[c];
		t->mn = min(t->mn, val);
	}
	//~ printf("\n");
}

void update(int val){
	for (int i = 1; i * i <= val; i++)
	{
		if(val % i != 0) continue;
		if(!root[i]){
			root[i] = new node();
		}
		add(val, i);
		//~ printf("inserindo %d em %d\n", val, i);
		
		if(i == val / i) continue;
		if(!root[val / i]){
			root[val / i] = new node();
		}
		add(val, val / i);
		//~ printf("inserindo %d em %d\n", val, val / i);
	}
}

pair<int, int> operator + (pair<int, int> a, pair<int, int> b){
	return mp(a.F + b.F, a.S + b.S);
}

pair<int, int> solve(trie t, int bit, bool menor){
	if(bit == -1) return mp(0, 0);
	pair<int, int> ans(-INF, -INF);
	int at = (x & (1 << bit)) != 0;
	//~ printf("estou em bit = %d  menor = %d  at = %d\n", bit, menor, at);
	if(menor){
		if(t->nxt[!at] && t->nxt[!at]->mn <= s - x){
			//~ printf("indo para %d\n", !at);
			ans = max(ans, mp(1 << bit, (!at) << bit) + solve(t->nxt[!at], bit - 1, menor));
			
		}else{
			if(t->nxt[at] && t->nxt[at]->mn <= s - x){
				ans = max(ans, mp(0, at << bit) + solve(t->nxt[at], bit - 1, menor));
			}
		}
	}else{
		if((s - x) & (1 << bit)){
			//~ printf("estou em bit = %d  menor = %d  at = %d\n", bit, menor, at);
			if(at == 0){
				if(t->nxt[1] && t->nxt[1]->mn <= s - x){
					//~ printf("indo para %d   (%d, %d)\n\n", 1, 1<<bit, 1<<bit);	
					ans = max(ans, mp(1 << bit, 1 << bit) + solve(t->nxt[1], bit - 1, false));
				}else{
					if(t->nxt[0] && t->nxt[0]->mn <= s - x){
						//~ printf("indo para %d\n", 0);
						ans = max(ans, mp(0, 0) + solve(t->nxt[0], bit - 1, true));
					}
				}
			}else{
				if(t->nxt[0] && t->nxt[0]->mn <= s - x){
					ans = max(ans, mp(1 << bit, 0) + solve(t->nxt[0], bit - 1, true));
				}else{
					if(t->nxt[1] && t->nxt[1]->mn <= s - x){
						ans = max(ans, mp(0, 1 << bit) + solve(t->nxt[1], bit - 1, false));
					}
				}
			}
		}else{
			//~ printf("estou em bit = %d  menor = %d  at = %d\n", bit, menor, at);
			//~ if(t->nxt[0]) printf("tem filho 0\n");
			//~ if(t->nxt[1]) printf("tem filho 1\n");
			if(at == 0){
				if(t->nxt[0] && t->nxt[0]->mn <= s - x){
					//~ printf("indo para %d   (%d, %d)\n", 0, 0, 0);
					ans = max(ans, mp(0, 0) + solve(t->nxt[0], bit - 1, false));
				}
			}else{
				if(t->nxt[0] && t->nxt[0]->mn <= s - x){
					//~ printf("indo para %d   (%d, %d)\n", 0, 1<<bit, 0);
					ans = max(ans, mp(1 << bit, 0) + solve(t->nxt[0], bit - 1, false));
				}
			}
		}
	}
	
	return ans;
}

int query(){
	if(s - x < 0) return -1;
	pair<int, int> ans(-1, -1), tmp;
	
	//~ printf("x = %d   k = %d   s = %d\n", x, k, s);
	for (int i = 1; i * i <= x; i++)
	{
		if(x % i != 0) continue;
		
		
		if(root[i] && i % k == 0){
			//~ printf("tentando achar resp em %d\n", i);
			//~ printf("i = %d\n", i);
			memo.clear();
			tmp = solve(root[i], BITMAX, false);
			//~ printf("(%d, %d)\n", tmp.F, tmp.S);
			if(tmp.F >= MAXN) tmp = mp(-1, -1);
			ans = max(ans, tmp);
		
		}
		if(i == x / i) continue;
		if(root[x / i] && (x / i) % k == 0){
			//~ printf("tentando achar resp em %d\n", x / i);
			//~ printf("x / i = %d\n", x / i);
			memo.clear();
			tmp = solve(root[x / i], BITMAX, false);
			if(tmp.F >= MAXN) tmp = mp(-1, -1);
			ans = max(ans, tmp);
		}
		
	}
	
	//~ printf("xor = %d   val = %d\n", ans.F, ans.S);
	return ans.S;
}

int main(){
	int n, op, val;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> op;
		if(op == 1){
			cin >> val;
			//~ printf("inserindo %d\n", val);
			update(val);
			//~ printf("inseriu %d\n", val);
		}else{
			cin >> x >> k >> s;
			cout << query() << "\n";
		}
	}
	
	
	
	return 0;
}
