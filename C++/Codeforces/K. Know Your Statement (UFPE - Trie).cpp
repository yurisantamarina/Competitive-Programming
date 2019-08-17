//~ http://codeforces.com/problemset/gymProblem/101628/K


#include <bits/stdc++.h>

using namespace std;
#define ALF 29
#define MAXN 3001010

struct node{
	node *nxt[ALF];
	int counter, end, c;
	set<int> ativo, termina;
	node(){
		counter = 0;
		end = 0;
		c = 0;
		ativo.clear();
		termina.clear();
		for (int i = 0; i < ALF; i++)
		{
			nxt[i] = NULL;
		}
	}
};

typedef node* trie;

trie root;
string v[MAXN];

void add(int id, string &s){
	trie t = root;
	int c;
	t->ativo.insert(id);
	t->counter++;
	
	for (int i = 0; i < (int)s.size(); i++)
	{
		c = s[i]-'a';
		if(!t->nxt[c]){
			trie son = new node();
			son->c = c;
			t->nxt[c] = son;
		}
		
		t = t->nxt[c];
		
		t->counter++;
		t->ativo.insert(id);
	}
	t->end++;
	t->termina.insert(id);
}

void remove(int id, string &s){
	trie t = root;
	int c;
	t->ativo.erase(id);
	t->counter--;
	
	for (int i = 0; i < (int)s.size(); i++)
	{
		c = s[i]-'a';
		
		t = t->nxt[c];
		
		t->counter--;
		t->ativo.erase(id);
	}
	t->end--;
	t->termina.erase(id);
}

void update(int pos, string &s){
	remove(pos, v[pos]);
	add(pos, s);
	v[pos] = s;
}

char query2(int l, int r, string &s){
	trie t = root;
	int c;
	set<int>::iterator it;
	
	for (int i = 0; i < (int)s.size(); i++)
	{
		c = s[i]-'a';
		if(t->nxt[c] && t->nxt[c]->counter > 0){
			t = t->nxt[c];
		}else return 'N';
		
		if(t->end > 0){
			it = t->termina.lower_bound(l);
			
			if(it == t->termina.end()) continue;
			
			if(*it <= r) return 'Y';
		}
	}
	
	return 'N';
}

char query3(int l, int r, string &s){
	trie t = root;
	int c;
	set<int>::iterator it;
	
	for (int i = 0; i < (int)s.size(); i++)
	{
		c = s[i]-'a';
		if(t->nxt[c] && t->nxt[c]->counter > 0){
			t = t->nxt[c];
		}else return 'N';
	}
	
	it = t->ativo.lower_bound(l);
	
	if(it == t->ativo.end()) return 'N';
	
	if(*it <= r) return 'Y';
	return 'N';
}

int main(){
	
	int n, q, l, r, pos, op;
	string s;
	
	root = new node();
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		add(i, v[i]);
	}
	
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> op;
		if(op == 1){
			cin >> pos >> s;
			update(pos, s);
		}else{
			cin >> l >> r >> s;
			if(op == 2) cout << query2(l, r, s) << "\n";
			else cout << query3(l, r, s) << "\n";
		}
	}
	
	
	
	
	
	return 0;
}
