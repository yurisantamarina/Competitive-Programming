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
#define MAXN 1000100
const ll A = 3;
const ll MOD = 9LL + 1e18;

string s;	

struct node{
	node* pai;
	node* suffix_link;
	node* nxt[256];
	bool end;
	int c;
	node(char letra, node* p){
		pai = p;
		suffix_link = NULL;
		for (int i = 0; i < 256; i++)
			nxt[i] = NULL;
		end = false;
		c = letra;
	}
	
	void add(int i){
		if(i==s.size()){
			end = true;
			return;
		}
		if(!nxt[s[i]]){
			nxt[s[i]] = new node(s[i], this);
		}
		
		nxt[s[i]]->add(i+1);
	}
	
	void build(){
		queue<node*> q;
		
		for (int i = 0; i < 256; i++)
		{
			if(nxt[i]) q.push(nxt[i]);
		}
		
		while (!q.empty())
		{
			node* t = q.front(); q.pop();
			
			char letra = t->c;
			node* w = t->pai->suffix_link;
			
			while (w && !w->nxt[letra])
				w = w->suffix_link;
			
			t->suffix_link = w ? w->nxt[letra] : this;
			t->end |= t->suffix_link->end;
			
			for (int i = 0; i < 256; i++)
			{
				if(t->nxt[i]) q.push(t->nxt[i]);
			}
		}
	}
	
};

node* trie;

node* sobe(node* aux, char letra){
	node* t = aux;
	while (t && !t->nxt[letra])
		t = t->suffix_link;
		
	return t ? t->nxt[letra] : trie;
}

int find(){
	int ans=0;
	node* t = trie;
	for (int i = 0; i < s.size(); i++)
	{
		int letra = s[i];
		
		t = sobe(t, letra);
		if(t->end){
			ans++;
			t = trie;
		}
			
	}
	
	return ans;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int n, m;
	
	while (cin >> n >> m)
	{
		if(n==0 && m==0) break;
		trie = new node('~', NULL);
		
		getline(cin, s);
		for (int i = 0; i < n; i++)
		{
			cin >> s;
			trie->add(0);
		}
		
		trie->build();
		int ans = 0;
		getline(cin, s);
		for (int i = 0; i < m; i++)
		{
			getline(cin, s);
			ans += find();
		}
		cout << ans << "\n";
	}
	
	
	return 0;
}
