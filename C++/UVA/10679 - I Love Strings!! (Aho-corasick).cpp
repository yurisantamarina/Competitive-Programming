#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};
const int N = 0;
const int MOD = 0;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

const int MAXPATTERN = 1002;
vector<string> pattern;
char found[1002];

struct node{
	node* pai;
	node* nxt[26];
	node* suffix_link;
	int c;
	bool end;
	bitset<MAXPATTERN> b;
	node(){
		pai = NULL;
		for(int i=0; i<26; i++) nxt[i] = NULL;
		suffix_link = NULL;
		end = false;
		b.reset();
	}
};
typedef node* trie;

trie root;

void add(string s, int idxPattern){
	trie t = root;
	
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'a';
		if(!t->nxt[c]){
			trie son = new node();
			son->pai = t;
			son->c = c;
			t->nxt[c] = son;
		}
		t = t->nxt[c];
	}
	t->end = true;
	t->b.set(idxPattern);
}

void buildSuffixLink(){
	queue<trie> q;
	q.push(root);
	
	trie t, w;
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		
		w = t->pai;
		if(w){
			w = w->suffix_link;
			
			while (w && !w->nxt[t->c])
			{
				w = w->suffix_link;
			}
			t->suffix_link = w==NULL ? root : w->nxt[t->c];
			t->end |= t->suffix_link->end;
			t->b |= t->suffix_link->b;
		}
		
		for (int i = 0; i < 26; i++)
		{
			if(t->nxt[i]) q.push(t->nxt[i]);
		}
	}
}

void find(string s){
	trie t = root;
	
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'a';
		
		if(t->nxt[c]){
			t = t->nxt[c];
		}else{
			
			while (t && !t->nxt[c])
			{
				t = t->suffix_link;
			}
			
			t = t==NULL ? root : t->nxt[c];
			
		}
		
		if(t->end){
			for (int j = 0; j < MAXPATTERN; j++)
			{
				if(t->b[j]){
					found[j] = 1;
				}
			}
			
		}
	}
	
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int t;
	cin >> t;
	while (t--)
	{
		string text, s;
		cin >> text;
		int n;
		cin >> n;
		root = new node();
		for (int i = 0; i < n; i++)
		{
			cin >> s;
			add(s, i);
		}
		buildSuffixLink();
		memset(found, 0, sizeof found);
		find(text);
		for (int i = 0; i < n; i++)
		{
			cout << (found[i] ? "y\n" : "n\n");
		}
		
		
	}
	
	
	
	return 0;
}
