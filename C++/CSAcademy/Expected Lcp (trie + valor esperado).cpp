#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define MAXN 1000010
#define pb push_back
typedef long long int ll;

struct node{
	node *nxt[26];
	ll end, lvl, sum;
	node(){
		memset(nxt, 0, sizeof nxt);
		end = lvl = sum = 0;
	}
};

typedef node* trie;
trie root;
ll prob[MAXN];

void add(string &s){
	trie t = root;
	ll c;
	for (ll i = 0; i < s.size(); i++)
	{
		c = s[i]-'a';
		if(!t->nxt[c]){
			trie son = new node();
			son->lvl = t->lvl + 1;
			t->nxt[c] = son;
		}
		t = t->nxt[c];
	}
	t->end++;
}

ll dfs(trie u){
	u->sum = u->end;
	
	for (ll i = 0; i < 26; i++)
	{
		if(!u->nxt[i]) continue;
		u->sum += dfs(u->nxt[i]);
	}
	
	ll ans = 0;
	for (ll i = 0; i < 26; i++)
	{
		if(!u->nxt[i]) continue;
		ans += ll(u->sum - u->end - u->nxt[i]->sum) * (u->nxt[i]->sum);
	}
	ans /= 2;
	
	if(u->end)
		ans += u->sum - u->end;
	
	prob[u->lvl] += ans;
	
	return u->sum;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	ll n;
	string s;
	root = new node();
	cin >> n;
	for (ll i = 0; i < n; i++)
	{
		cin >> s;
		add(s);
	}
	dfs(root);
	
	double ans = 0;
	ll tot = ((ll)n * (n-1)) / 2;
	for (ll i = 0; i < MAXN; i++)
		ans += i * (1.0 * prob[i] / tot);
	
	
	cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}
