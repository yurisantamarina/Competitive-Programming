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
	node* nxt[2];
	int c;
	int cnt;
	
	node(){
		nxt[0] = nxt[1] = NULL;
		cnt = 0;
	}
	
};

typedef node* trie;
trie root;

void add(int x){
	bitset<30> b(x);
	trie t = root;
	string s = b.to_string();
	t->cnt++;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i]-'0';
		if(!t->nxt[c]){
			trie son = new node();
			son->c = c;
			t->nxt[c] = son;
		}
		t = t->nxt[c];
		t->cnt++;
	}
}

string q;
string K;
ll query(int pos, trie t){
	if(pos==q.size()) return 0;
	
	ll ans = 0LL;
	if(K[pos] == '0'){
		if(q[pos] == '0'){
			if(t->nxt[0]) ans += query(pos+1, t->nxt[0]);
		}else{
			if(t->nxt[1]) ans += query(pos+1, t->nxt[1]);
		}
	}else{//K[pos] == '1'
		if(q[pos] == '0'){
			if(t->nxt[0]) ans += t->nxt[0]->cnt;
			if(t->nxt[1]) ans += query(pos+1, t->nxt[1]);
		}else{
			if(t->nxt[0]) ans += query(pos+1, t->nxt[0]);
			if(t->nxt[1]) ans += t->nxt[1]->cnt;
		}
	}
	
	return ans;
}

int main () {
	
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	int tc, n, k, x;
	trie t;
	cin >> tc;
	while (tc--)
	{
		root = new node();
		cin >> n >> k;
		bitset<30> b(k);
		K = b.to_string();
		add(0);
		ll ans = 0LL;
		int acc = 0;
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> x;
			sum += (x >= k);
			acc ^= x;
			bitset<30> b(acc);
			q = b.to_string();
			t = root;
			
			ans += query(0, t);
			add(acc);
			
		}
		cout << ans << "\n";
	}
	
		
	return 0;
}
