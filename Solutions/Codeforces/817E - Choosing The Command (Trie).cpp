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
const ll MOD = 1000000007LL;
const int INF = 1e9 + 10;
const ll LLINF = 1e18 + 10;
#define MAXN 305010

struct node{
	node* nxt[2];
	node* pai;
	int c;
	int cnt;
	node(){
		nxt[0] = NULL;
		nxt[1] = NULL;
		pai = NULL;
		cnt = 0;
	}
};

typedef node* trie;
trie root;

void add(int n){
	
 	bitset<28> b(n);
	string s = b.to_string();
	trie t = root;
	int c;
	t->cnt++;
	for (int i = 0; i < s.size(); i++)
	{
		
		c = s[i]-'0';
		if(!t->nxt[c]){
			trie son = new node();
			son->pai = t;
			t->nxt[c] = son;
			son->c = c;
		}
		
		t = t->nxt[c];
		t->cnt++;
	}
	
}

void del(int n){
	bitset<28> b(n);
	string s = b.to_string();
	trie t = root;
	int c;
	t->cnt--;
	for (int i = 0; i < s.size(); i++)
	{
		c = s[i]-'0';
		t = t->nxt[c];
		
		t->cnt--;
	}
	
}

string p, l;

int solve(int pos, trie t){
	//~ if(!t || t->cnt==0) return 0;
	if(pos==p.size()) return 0;
	
	int ans=0;
	if(l[pos]=='0'){
		if(p[pos]=='0'){
			if(t->nxt[0] && t->nxt[0]->cnt)
				ans += solve(pos+1, t->nxt[0]);
		}else{
			if(t->nxt[1] && t->nxt[1]->cnt)
				ans += solve(pos+1, t->nxt[1]);
		}
	}else{//l[pos]=='1'
		if(p[pos]=='0'){
			if(t->nxt[0] && t->nxt[0]->cnt)
				ans += t->nxt[0]->cnt;
			if(t->nxt[1] && t->nxt[1]->cnt)
				ans += solve(pos+1, t->nxt[1]);
		}else{
			if(t->nxt[0] && t->nxt[0]->cnt)
				ans += solve(pos+1, t->nxt[0]);
				
			if(t->nxt[1] && t->nxt[1]->cnt)
				ans += t->nxt[1]->cnt;
		}
	}
	
	return ans;
}

int query(int pers, int lea){
	bitset<28> b1(pers);
	p = b1.to_string();
	
	bitset<28> b2(lea);
	l = b2.to_string();
	
	//~ cout << "p = " << p << "  l = " << l << endl;
	return solve(0, root);
}

int main () {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	root = new node();
	int val, op, pers, lea;
	for (int i = 0; i < n; i++)
	{
		cin >> op;
		if(op==1){
			cin >> val;
			add(val);
		}else if(op==2){
			cin >> val;
			del(val);
		}else{
			cin >> pers >> lea;
			cout << query(pers, lea) << "\n";
		}
	}
	
	
	
	return 0;
}
