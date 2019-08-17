//~ http://codeforces.com/gym/101174/attachments

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
ll MOD = 1000003;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;

int TAM;

struct node{
	node* pai;
	node* nxt[256];
	node* suffix_link;
	char c;
	bool end;
	int number;
	node(){
		pai = NULL;
		for (int i = 0; i < 256; i++)
			nxt[i] = NULL;
		suffix_link = NULL;
		end = false;
	}
};

typedef node* trie;
trie root;
int cnt=1;

ll dp[21][2][2][2][1000];
string pattern[60];

void add(string s){
	trie t = root;
	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if(!t->nxt[c]){
			trie son = new node();
			son->number = cnt++;
			son->pai = t;
			son->c = c;
			t->nxt[c] = son;
		}
		t = t->nxt[c];

	}
	t->end = true;
}

void buildSuffixLink(){
	queue<trie> q;
	q.push(root);
	
	while (!q.empty())
	{
		trie t = q.front();
		q.pop();
		
		trie w = t->pai;
		if(w){
			w = w->suffix_link;
			while (w && !w->nxt[t->c])
			{
				w = w->suffix_link;
			}
			t->suffix_link = w==NULL ? root : w->nxt[t->c];
			t->end |= t->suffix_link->end;
		}
		
		for (int i = 0; i < 256; i++)
		{
			if(t->nxt[i]) q.push(t->nxt[i]);
		}
		
	}
	
}

trie getNode(trie t, char c){
	if(!(c >= '0' && c <= '9')) c = tolower(c);
	else if(c=='3') c = 'e';
	else if(c=='1') c = 'i';
	else if(c=='0') c = 'o';
	else if(c=='5') c = 's';
	else if(c=='7') c = 't';
	
	while (t && !t->nxt[c])
	{
		t = t->suffix_link;
	}
	
	t = t==NULL ? root : t->nxt[c];
	
	return t;
}

ll solve(int pos, bool temUpper, bool temLower, bool temDigito, int no, trie endereco){
	if(pos==TAM) return !endereco->end && temUpper && temLower && temDigito;
	if(dp[pos][temUpper][temLower][temDigito][no] != -1) return dp[pos][temUpper][temLower][temDigito][no];
	if(endereco->end) return 0LL;
	
	ll ans = 0LL;
	trie t;
	for (char i = 'a'; i <= 'z'; i++)
	{
		t = getNode(endereco, i);
		ans += solve(pos+1, temUpper, true, temDigito, t->number, t);
		ans%=MOD;
	}
	
	for (char i = 'A'; i <= 'Z'; i++)
	{
		t = getNode(endereco, i);
		ans += solve(pos+1, true, temLower, temDigito, t->number, t);
		ans%=MOD;
	}
	
	for (char i = '0'; i <= '9'; i++)
	{
		t = getNode(endereco, i);
		ans += solve(pos+1, temUpper, temLower, true, t->number, t);
		ans%=MOD;
	}
	
	return dp[pos][temUpper][temLower][temDigito][no] = ans;
}

string ajusta(string s){
	for (int i = 0; i < s.size(); i++)
	{
		if(!(s[i] >= '0' && s[i] <= '9')) s[i] = tolower(s[i]);
		else if(s[i]=='3') s[i] = 'e';
		else if(s[i]=='1') s[i] = 'i';
		else if(s[i]=='0') s[i] = 'o';
		else if(s[i]=='5') s[i] = 's';
		else if(s[i]=='7') s[i] = 't';
	}
	return s;
}

int main () {
	
	int l, r, qtdPattern;
	root = new node();
	root->number = 0;
	cin >> l >> r;
	cin >> qtdPattern;
	for (int i = 0; i < qtdPattern; i++)
	{
		cin >> pattern[i];
		pattern[i] = ajusta(pattern[i]);
		add(pattern[i]);
	}
	buildSuffixLink();
	
	ll ans = 0LL;
	for (int i = l; i <= r; i++)
	{
		memset(dp, -1, sizeof dp);
		TAM = i;
		ans += solve(0, false, false, false, 0, root);
		ans%=MOD;
	}
	
	cout << ans << "\n";
	
	
	
	
	
	
	
	return 0;
}
