#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;

struct node{
	int cnt;
	int c;
	node* nxt[26];
	node(){
		cnt = 0;
		for (int i = 0; i < 26; i++)
		{
			nxt[i] = NULL;
		}
	}
};

typedef node* trie;
trie root, t;

void add(string s){
	t = root;
	int c;
	for (int i = 0; i < s.size(); i++)
	{
		c = s[i]-'A';
		if(!t->nxt[c]){
			trie son = new node();
			son->c = c;
			t->nxt[c] = son;
		}
		t = t->nxt[c];
		t->cnt++;
	}
}

int tira;

int conta(string s){
	t = root;
	int c;
	int ans = 0;
	for (int i = 0; i < s.size(); i++)
	{
		c = s[i]-'A';
		if(!t->nxt[c]) break;
		t = t->nxt[c];
		t->cnt--;
		if(t->cnt < 0) tira++;
		ans++;
	}
	return ans;
}



int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int n;
	string s;
	while (cin >> n, n!=-1)
	{
		root = new node();
		for (int i = 0; i < n; i++)
		{
			cin >> s;
			add(s);
		}
		
		int ans = 0;
		tira = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> s;
			ans += conta(s);
		}
		
		//~ cout << tira << "\n";
		ans -= tira;
		cout << ans << "\n";
	}
	
	
	
	
	return 0;
}
