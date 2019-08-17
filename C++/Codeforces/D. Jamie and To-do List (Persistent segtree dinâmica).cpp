#include <bits/stdc++.h>

using namespace std;
#define MAXN 1000000010

struct node{
	node *l, *r;
	int val;
	node(){
		l = NULL;
		r = NULL;
		val = 0;
	}
};

int merge(node *a, node* b){
	int x = 0, y = 0;
	if(a) x = a->val;
	if(b) y = b->val;
	return x+y;
}

node* update(node* no, int l, int r, int pos, int val, int op){
	node* nw = new node();
	*nw = *no;
	if(l == r){
		if(op == 0)
			nw->val += val;
		else
			nw->val = val;
			
		return nw;
	}
	int mid = (l + r)/2;
	int a = 0, b = 0;
	if(pos <= mid){
		if(!no->l) no->l = new node();
		nw->l = update(no->l, l, mid, pos, val, op);
		a = nw->l->val;
	}else{
		if(!no->r) no->r = new node();
		nw->r = update(no->r, mid+1, r, pos, val, op);
		b = nw->r->val;
	}
	
	nw->val = merge(nw->l, nw->r);
	return nw;
}

int query(node* no, int l, int r, int i, int j){
	if(l > j || r < i) return 0;
	if(i <= l && r <= j) return no->val;
	
	int mid = (l+r)/2;
	int a = 0, b = 0;
	if(no->l) a = query(no->l, l, mid, i, j);
	if(no->r) b = query(no->r, mid+1, r, i, j);
	
	return a+b;
}

node *dias[101010];
node *priAt[101010];
map<string, int> mapa;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	dias[0] = new node();
	priAt[0] = new node();
	int q, xi, aux, idx = 1, at = 1, d, u;
	string op, ai;
	cin >> q;
	
	while (q--)
	{
		cin >> op;
		//~ cout << endl;
		if(op == "set"){
			cin >> ai >> xi;
			if(mapa.count(ai)==0) mapa[ai]=idx++;
			u = mapa[ai];
			//~ printf("set %s u =%d at = %d\n", ai.c_str(), u, at);
			aux = query(priAt[at-1], 1, MAXN, u, u);
			
			if(aux){
				//~ printf("tirando de %d e botando em %d\n", aux, xi);
				dias[at] = update(dias[at-1], 1, MAXN, aux, -1, 0);
				dias[at] = update(dias[at], 1, MAXN, xi, 1, 0);
			}else{
				//~ printf("botando em %d\n", xi);
				dias[at] = update(dias[at-1], 1, MAXN, xi, 1, 0);
			}
			
			priAt[at] = update(priAt[at-1], 1, MAXN, u, xi, 1);
			
			at++;
			//~ printf("SOMA = %d\n", query(dias[at-1], 1, MAXN, 1, MAXN));
		}else if(op == "remove"){
			cin >> ai;
			if(mapa.count(ai)==0) mapa[ai]=idx++;
			u = mapa[ai];
			aux = query(priAt[at-1], 1, MAXN, u, u);
			if(aux){
			//~ printf("remove %s u = %d at = %d aux = %d\n", ai.c_str(), u, at, aux);
			
				dias[at] = update(dias[at-1], 1, MAXN, aux, -1, 0);
				priAt[at] = update(priAt[at-1], 1, MAXN, u, 0, 1);
			}else{
				dias[at] = dias[at-1];
				priAt[at] = priAt[at-1];
			}
			
			at++;
		}else if(op == "query"){
			cin >> ai;
			if(mapa.count(ai)==0) mapa[ai]=idx++;
			u = mapa[ai];
			//~ cout << "query = " << ai << " u = " << u << " at = " << at << endl;
			
			aux = query(priAt[at-1], 1, MAXN, u, u);
			//~ printf("aux = %d [%d, %d] at = %d\n", aux, 1, aux-1, at);
			if(aux) cout << query(dias[at-1], 1, MAXN, 1, aux-1) << "\n";
			else cout << "-1\n";
			cout << flush;
			dias[at] = dias[at-1];
			priAt[at] = priAt[at-1];
			
			at++;
		}else{
			cin >> d;
			//~ at -= d;
			priAt[at] = priAt[at - d - 1];
            dias[at] = dias[at - d - 1];
			//~ priAt[at] = priAt[at - 1];
            //~ dias[at] = dias[at - 1];
			//~ cout << "at = " << at << endl;
			at++;
		}
	}
	
	
	return 0;
}
