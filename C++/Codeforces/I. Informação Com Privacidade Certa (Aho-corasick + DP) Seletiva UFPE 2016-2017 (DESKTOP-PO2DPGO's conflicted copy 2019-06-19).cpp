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



struct node{
	node* pai;
	node* nxt[27];
	node* suffix_link;
	int c;
	bool end;
	bitset<1002> b;
	node(){
		pai = NULL;
		suffix_link = NULL;
		for (int i = 0; i < 26; i++)
			nxt[i] = NULL;
		end = false;
		b.reset();
	}
};


struct rec{
	int fim, id;
	rec(){}
	rec(int b, int c){
		fim = b;
		id = c;
	}
};

typedef node* trie;
trie root;
vector<string> pattern;
vector<int> cost;
int qtdPatterns;
vector<rec> v[100010];
map<string, int> mapa;
ll dp[100010];

void add(string s, int idx){
	trie t = root;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'a';
		if(t->nxt[c] == NULL){
			trie son = new node();
			son->pai = t;
			son->c = c;
			t->nxt[c] = son;
		}
		
		t = t->nxt[c];
		if(i==s.size()-1){
			t->end = true;
			t->b.set(idx);
		}
	}
}

void buildSuffixLink(){
	queue<trie> q;
	q.push(root);
	
	trie t;
	while (!q.empty())
	{
		t = q.front(); q.pop();
		
		trie w = t->pai;
		if(w!=NULL){
			w = w->suffix_link;
			while (w != NULL && w->nxt[t->c] == NULL)
			{
				w = w->suffix_link;
			}
			
			t->suffix_link = w==NULL ? root : w->nxt[t->c];
			t->end |= t->suffix_link->end;
			t->b |= t->suffix_link->b;
		}
		for (int i = 0; i < 26; i++)
		{
			if(t->nxt[i] != NULL) q.push(t->nxt[i]);
		}
	}
}


void find(string s){
	trie t = root;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'a';
		if(t->nxt[c] == NULL){
			while (t != NULL && t->nxt[c] == NULL)
			{
				t = t->suffix_link;
			}
			if(t==NULL){
				t = root;
			}else{
				t = t->nxt[c];
			}
		}else{
			t = t->nxt[c];
		}
		
		if(t->end){
			for (int j = 0; j < 1002; j++)
			{
				if(t->b[j]){
					v[i-pattern[j].size()+1].pb(rec(i, j));
				}
			}
		}
	}
}

string text;

ll solve(int pos){
	if(pos>=text.size()) return 0LL;
	if(dp[pos]!=-1) return dp[pos];
	
	ll ans = solve(pos+1);
	for (int i = 0; i < v[pos].size(); i++)
	{
		ans = max(ans, cost[v[pos][i].id] + solve(v[pos][i].fim+1));
	}
	
	return dp[pos] = ans;
}

int main () {
	cin >> text;
	cin >> qtdPatterns;
	string x;
	int y;
	
	root = new node();
	
	for (int i = 0; i < qtdPatterns; i++)
	{
		cin >> x >> y;
		pattern.pb(x);
		cost.pb(y);
		add(pattern[i], i);
	}
	
	//~ for(auto i : mapa){
		//~ pattern.pb(i.F);
		//~ cost.pb(i.S);
		//~ add(i.F, pattern.size()-1);
	//~ }
	buildSuffixLink();
	
	find(text);
	
	memset(dp, -1, sizeof dp);
	
	//~ for (int i = 0; i <= text.size(); i++)
	//~ {
		//~ for (int j = 0; j < v[i].size(); j++)
		//~ {
			//~ cout << "comeca em " << i << endl;
			//~ cout << pattern[v[i][j].id] << " " << v[i][j].ini << " " << v[i][j].fim << endl;
		//~ }
	//~ }
	
	cout << solve(0) << endl;
	
	
	return 0;
}
