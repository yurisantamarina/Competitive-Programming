#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
#define mp make_pair
#define pb push_back

struct qry{
	string op;
	int x, y;
	qry(){}
	qry(string a, int b, int c){
		op = a;
		x = b;
		y = c;
	}
};

vector<qry> Q;
int st[4*MAXN], n;
unordered_map<int, int> mapax, mapay, revx, revy;
multiset<int> s[MAXN]; 
set<int> sx;

void update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(l == r){
		st[no] = val;
		return;
	}
	int mid = (l+r)/2, nxt = 2*no;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = max(st[nxt], st[nxt+1]);
}

bool ok;
int ans;

void query(int no, int l, int r, int i, int j, int y){
	if(ok || r < i || l > j) return;
	if(l == r){
		if(st[no] > y){
			ans = l;
			ok = true;
		}
		return;
	}
	
	int mid = (l+r)/2, nxt = 2*no;
	if(i <= l && r <= j){
		if(st[nxt] > y) return query(nxt, l, mid, i, j, y);
		else if(st[nxt+1] > y) return query(nxt+1, mid+1, r, i, j, y);
		//~ else{
			//~ ok = true;
			//~ ans = -1;
			//~ return;
		//~ }
		return;
	}
	
	query(nxt, l, mid, i, j, y);
	query(nxt+1, mid+1, r, i, j, y);
}

int getX(int l, int r, int y){
	ok = false;
	
	ans = -1;
	query(1, 1, n, l, r, y);
	
	if(!ok) ans = -1;
	return ans;
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	
	int q, x, y, val;
	string op;
	char opp[10];
	scanf("%d", &q);
	while (q--)
	{
		scanf(" %s %d %d", opp, &x, &y);
		sx.insert(x);
		//~ sy.insert(y);
		//~ sx.pb(x);
		//~ sy.pb(y);
		Q.pb(qry(opp, x, y));
	}
	
	//~ sort(sx.begin(), sx.end());
	//~ sort(sy.begin(), sy.end());
	
	n = 0;
	int idx = 1;
	for(auto i : sx){
		mapax[i] = idx++;
		//~ n = max(n, mapax[i]);
		revx[mapax[i]] = i;
	}
	n = idx;
	//~ n++;
	//~ for(auto i : sy){
		//~ mapay[i] = lower_bound(sy.begin(), sy.end(), i) - sy.begin() + 1;
		//~ revy[mapay[i]] = i;
	//~ }
	
	//~ build(1, 1, n);
	
	for (int i = 0; i < (int)Q.size(); i++)
	{
		//~ Q[i].x = mapax[Q[i].x];
		//~ Q[i].y = mapay[Q[i].y];
		x = mapax[Q[i].x];
		y = Q[i].y;
		if(Q[i].op == "add"){
			s[x].insert(y);
			//~ printf("inserindo y = %d em x = %d\n", revy[y], revx[x]);
			val = *s[x].rbegin();
			update(1, 1, n, x, val);
			//~ printf("x = %d  val = %d\n", revx[x], revy[val]);
		}else if(Q[i].op == "remove"){
			s[x].erase(s[x].find(y));
			val = (int)s[x].size() ? *s[x].rbegin() : 0;
			update(1, 1, n, x, val);
		}else{
			x = getX(x+1, n, y);
			if(x == -1) printf("-1\n");
			else printf("%d %d\n", revx[x], *s[x].upper_bound(y));
		}
	}
	
	
	return 0;
}
