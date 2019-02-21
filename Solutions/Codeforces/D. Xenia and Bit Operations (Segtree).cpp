#include <bits/stdc++.h>

using namespace std;

#define MAXN 1<<17 + 1
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 1000000000
typedef long long int ll;

int st[4*MAXN];
int v[MAXN];
int n;

int merge(int esq, int dir, int lvl){
	if(lvl%2 == 0) return st[esq] | st[dir];
	return st[esq] ^ st[dir];
}

void build(int no, int l, int r, int lvl){
	if(l == r){
		st[no] = v[l];
		return;
	}
	int mid = (l+r)/2, nxt = 2*no;
	build(nxt, l, mid, lvl^1);
	build(nxt+1, mid+1, r, lvl^1);
	st[no] = merge(nxt, nxt+1, lvl);
	
}

void update(int no, int l, int r, int pos, int val, int lvl){
	if(pos < l || pos > r) return;
	if(pos == l && l == r){
		st[no] = val;
		return;
	}
	int mid = (l+r)/2, nxt = 2*no;
	update(nxt, l, mid, pos, val, lvl^1);
	update(nxt+1, mid+1, r, pos, val, lvl^1);
	st[no] = merge(nxt, nxt+1, lvl);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q, p, b, tam;
	cin >> n >> q;
	tam = 1<<n;
	for (int i = 0; i < tam; i++)
	{
		cin >> v[i];
	}
	build(1, 0, tam-1, !(n%2));
	for (int i = 0; i < q; i++)
	{
		cin >> p >> b;
		p--;
		update(1, 0, tam-1, p, b, !(n%2));
		cout << st[1] << "\n";
	}
	
	
	
	
	
	
	
	
	return 0;
}
