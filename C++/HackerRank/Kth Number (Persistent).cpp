#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010

struct node{
	int sum, l, r;
};

node st[10101010];
int nxt = 1;
int root[MAXN];
int v[MAXN];
vector<int> vet[MAXN];


int update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return no;
	int clone = nxt++;
	st[clone] = st[no];
	if(l==r){
		st[clone].sum += val;
		return clone;
	}
	int mid = (l+r)/2;
	
	st[clone].l = update(st[clone].l, l, mid, pos, val);
	st[clone].r = update(st[clone].r, mid+1, r, pos, val);
	
	st[clone].sum = st[st[clone].l].sum + st[st[clone].r].sum;
	
	return clone;
}

int query(int noL, int noR, int l, int r, int k){
	if(l == r){
		return v[l];
	}
	int sumEsq = st[st[noR].l].sum - st[st[noL].l].sum;
	
	int mid = (l+r)/2;
	if(sumEsq >= k) return query(st[noL].l, st[noR].l, l, mid, k);
	return query(st[noL].r, st[noR].r, mid+1, r, k - sumEsq);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q, l, k;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		vet[v[i]].push_back(i);
	}
	
	root[0] = 0;
	for (int i = 1; i < MAXN; i++)
	{
		root[i] = root[i-1];
		for (int j = 0; j < (int)vet[i].size(); j++)
		{
			root[i] = update(root[i], 1, n, vet[i][j], 1);
		}
	}
	
	for (int i = 0; i < q; i++)
	{
		cin >> l >> k;
		cout << query(root[l-1], root[MAXN-1], 1, n, k) << "\n";
	}
	
	
	
	return 0;
}
