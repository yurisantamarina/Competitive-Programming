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

string s1, s2;
int dp[102][102][1000];
int cnt;

struct node{
	node* pai;
	node* nxt[26];
	node* suffix_link;
	int c;
	int number;
	bool end;
	node(){
		pai = NULL;
		for(int i = 0; i < 26; i++)
			nxt[i] = NULL;
		suffix_link = NULL;
		end = false;
	}
};
typedef node* trie;
trie root;

void add(string s){
	trie t = root;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'A';
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
		if(w){
			w = w->suffix_link;
			while (w && !w->nxt[t->c])
			{
				w = w->suffix_link;
			}
			t->suffix_link = w==NULL ? root : w->nxt[t->c];
			t->end |= t->suffix_link->end;
		}
		
		for (int i = 0; i < 26; i++)
		{
			if(t->nxt[i]) q.push(t->nxt[i]);
		}
	}
}

trie get(trie t, char ch){
	int c = ch-'A';
	while (t && !t->nxt[c])
	{
		t = t->suffix_link;
	}
	t = t==NULL ? root : t->nxt[c];
	return t;
}

int lcs(int a, int b, int node_number, trie at){
	if(a==s1.size() || b==s2.size()) return dp[a][b][node_number] = 0;
	if(dp[a][b][node_number]!=-1) return dp[a][b][node_number];
	
	int ans = 0;
	if(s1[a] == s2[b]){
		trie t = get(at, s1[a]);
		if(t->end){
			ans = lcs(a+1, b+1, node_number, at);
		}else{
			ans = max(1 + lcs(a+1, b+1, t->number, t), lcs(a+1, b+1, node_number, at));//nem sempre é bom pegar um caractere igual pois ele pode ser o inicio do virus
			//Ex: ABBB ABBB ABB: Se pegar o A, o maximo que pode formar é AB, e a resposta é BBB
		}
	}else{
		ans = max(lcs(a+1, b, node_number, at), lcs(a, b+1, node_number, at));
	}
	
	return dp[a][b][node_number] = ans;
}


void path(int a, int b, int node_number, trie at){
	if(a==s1.size() || b==s2.size()){
		return;
	}
	
	int ans = 0;
	if(s1[a] == s2[b]){
		trie t = get(at, s1[a]);
		if(t->end){
			path(a+1, b+1, node_number, at);
		}else{
			if(dp[a][b][node_number] == 1 + dp[a+1][b+1][t->number]){
				cout << s1[a];
				path(a+1, b+1, t->number, t);
			}else{
				path(a+1, b+1, node_number, at);
			}
			
		}
	}else{
		if(dp[a][b][node_number] == dp[a+1][b][node_number]){
			path(a+1, b, node_number, at);
		}else{
			path(a, b+1, node_number, at);
		}
	}
	
}




int main () {
	
	string virus;
	cin >> s1 >> s2;
	cin >> virus;
	
	string aux;
	
	root = new node();
	root->number = 0;
	cnt = 1;
	//~ for (int i = 0; i < virus.size(); i++)
	//~ {
		//~ aux = "";
		//~ for (int j = i; j < virus.size(); j++)
		//~ {
			//~ aux += virus[j];
			//~ add(aux);
		//~ }
	//~ }
	add(virus);
	buildSuffixLink();
	
	memset(dp, -1, sizeof dp);
	int ans = lcs(0, 0, root->number, root);
	//~ cout << ans << endl;
	if(ans)
		path(0, 0, 0, root);
	else cout << 0;
	cout << "\n";
	return 0;
}
