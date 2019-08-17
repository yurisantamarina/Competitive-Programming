#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define MAXN 101010
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}


struct Q{
	int l, r, k;
	Q(){}
	Q(int a, int b, int c){
		l = a;
		r = b;
		k = c;
	}
};

struct node{
	int sum, l ,r;
};

node st[10101010];
int v[MAXN];
int root[MAXN];
unordered_map<int, int> mapa;
set<int> s;
vector<Q> queries;
int nxt = 1;

int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	int clone = nxt++;
	st[clone] = st[no];
	if(l == r){
		st[clone].sum += val;
		return clone;
	}
	
	int mid = (l+r)/2;
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

int query(int noL, int noR, int l, int r, int i, int j){
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return st[noR].sum - st[noL].sum;
	
	int mid = (l+r)/2;
	return query(st[noL].l, st[noR].l, l, mid, i, j) + query(st[noL].r, st[noR].r, mid+1, r, i, j);
}

int main(){
	
	int n, q, l, r, k;
	scanint(n);
	for (int i = 1; i <= n; i++){
		scanint(v[i]);
		s.insert(v[i]);
	}
	int idx = 0;
	for (auto i : s)
		mapa[i] = idx++;
	
	root[0] = 0;
	for (int i = 1; i <= n; i++){
		v[i] = mapa[v[i]];
		root[i] = update(root[i-1], 0, idx, v[i], 1);
	}
	
	scanint(q);
	set<int>::iterator it;
	
	for (int i = 0; i < q; i++)
	{
		scanint(l);
		scanint(r);
		scanint(k);
		it = s.upper_bound(k);
		if(it == s.end()){
			printf("0\n");
		}else{
			printf("%d\n", query(root[l-1], root[r], 0, idx, mapa[*it], idx));
		}	
	}
	
	return 0;
}
