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
	node* nxt[10];
	node* suffix_link;
	bool end;
	int c;
	int number;
	node(){
		pai = NULL;
		for(int i = 0; i < 10; i++)
			nxt[i] = NULL;
		suffix_link = NULL;
		end = false;
		number = -1;
	}
};
typedef node* trie;
trie root;

string s;
ll dp[19][2][5000*19];
int cnt;



void add(string s){
	trie t = root;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'0';
		if(!t->nxt[c]){
			trie son = new node();
			son->c = c;
			son->pai = t;
			son->number = cnt++;
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
		if(w != NULL){
			w = w->suffix_link;
			while (w != NULL && w->nxt[t->c] == NULL)
			{
				w = w->suffix_link;
			}
			t->suffix_link = w == NULL ? root : w->nxt[t->c];
			t->end |= t->suffix_link->end;
		}
		
		for (int i = 0; i < 10; i++)
		{
			if(t->nxt[i]) q.push(t->nxt[i]);
		}
		
	}
	
}

trie get(trie t, int c){
	while (t && !t->nxt[c])
	{
		t = t->suffix_link;
	}
	t = t==NULL ? root : t->nxt[c];
	return t;
}

ll solve(int pos, bool bate, bool comecou, int node_number, trie endereco){
	if(pos==s.size()) return !endereco->end;
	if(dp[pos][bate][node_number]!=-1) return dp[pos][bate][node_number];
	if(endereco->end && comecou){
		return 0LL;
	}
	
	trie t;
	ll ans = 0LL;
	if(bate){
		for (int i = 0; i <= s[pos]-'0'; i++)
		{
			t = get(endereco, i);
			if(i==s[pos]-'0') ans += solve(pos+1, true, i ? true : comecou, t->number, t);
			else ans += solve(pos+1, false, i ? true : comecou,t->number, t);
		}
	}else{
		for (int i = 0; i < 10; i++)
		{
			t = get(endereco, i);
			ans += solve(pos+1, false, i ? true : comecou,t->number, t);
		}
	}
	
	return dp[pos][bate][node_number] = ans;
}

string to_stringg(ll n){
	if(!n) return "0";
	string ss="";
	while (n)
	{
		ss += (n%10)+'0';
		n/=10;
	}
	reverse(ss.begin(), ss.end());
	return ss;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int x;
	string aux;
	ll n;
	while (cin >> n)
	{
		if(!n) break;
		s = to_stringg(n);
		cin >> x;
		root = new node();
		root->number = 0;
		cnt = 1;
		while (x--)
		{
			cin >> aux;
			add(aux);
		}
		buildSuffixLink();
		for (int i = 0; i <= s.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k <= cnt; k++)
				{
					dp[i][j][k] = -1;
				}
			}
		}
		
		cout << n+1 - solve(0, true, false, 0, root) << "\n";
	}
	
		
	return 0;
}
