#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 1000000000
typedef long long int ll;
#define MAXN 600100
#define A 3

struct node{
	int c;
	node *nxt[A];
	bool end;
	node(){
		for (int i = 0; i < A; i++)
		{
			nxt[i] = NULL;
		}
		end = false;
	}
};

typedef node* trie;
trie root;

void add(string &s){
	trie t = root;
	int c;
	for (int i = 0; i < (int)s.size(); i++)
	{
		c = s[i]-'a';
		if(!t->nxt[c]){
			trie son = new node();
			son->c = c;
			t->nxt[c] = son;
		}
		t = t->nxt[c];
	}
	t->end = true;
}

bool solve(string &s, int idx, trie t, int cnt){
	if(cnt > 1) return false;
	if(idx == (int)s.size()) return t->end && cnt == 1;
	
	bool ans = false;
	for (int i = 0; !ans && i < A; i++)
	{
		if(t->nxt[i]){
			ans |= solve(s, idx+1, t->nxt[i], cnt + (s[idx]-'a' != i));
		}
	}
	
	return ans;
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	string s;
	cin >> n >> m;
	root = new node();
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		add(s);
	}
	for (int i = 0; i < m; i++)
	{
		cin >> s;
		cout << (solve(s, 0, root, 0) ? "YES\n" : "NO\n");
	}
	
	
	
	return 0;
}s
