#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
#define MAXN 100010

struct node{
	node* nxt[26];
	int cnt;
	int c;
	node(){
		for (int i = 0; i < 26; i++)
		{
			nxt[i] = NULL;
		}
		cnt = 0;
	}
};

typedef node* trie;
trie root;

void add(string s){
	trie t = root;
	t->cnt++;
	//~ if(s=="GATTACA") cout << s << endl;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'A';
		t->cnt++;
		if(!t->nxt[c]){
			trie son = new node();
			son->c = c;
			t->nxt[c] = son;
		}
		//~ if(s=="GATTACA"){
			//~ cout << t->cnt << endl;
		//~ }
		t = t->nxt[c];
	}
	t->cnt++;
}
string aux = "ACGT";
int ans = 0;
string saida;
int f;

void find(trie t, int p, string s){
	if(t->cnt < 2) return;
	if(p > ans){
		saida = s;
		ans = p;
		f = t->cnt;
	}
	for (int i = 0; i < 4; i++)
	{
		int c = aux[i]-'A';
		if(t->nxt[c]){
			find(t->nxt[c], p+1, s + aux[i]);
		}
	}
	
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
		
	int t;
	cin >> t;
	string s;
	
	while (t--)
	{
		root = new node();
		cin >> s;
		
		for (int i = 0; i < s.size(); i++)
		{
			//~ cout << s.substr(i) << endl;
			add(s.substr(i));
		}
		
		ans = 0;
		find(root, 0, "");
		if(ans){
			cout << saida << " " << f << endl;
		}else{
			cout << "No repetitions found!\n";
		}
	}
	
	
	
	
	
	
	
	return 0;
}
