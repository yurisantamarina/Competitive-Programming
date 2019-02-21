#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define MAXN 301010

struct person{
	int A, H, id;
	person(){}
	person(int a, int b, int c){
		A = a;
		H = b;
		id = c;
	}
	bool operator < (person other) const{
		if(H == other.H) return A < other.A;
		return H < other.H;
	}
};

int n, A[MAXN], H[MAXN], ans[MAXN];
vector<person> coder;
int mapeiaLeft(int l){
	return lower_bound(H + 1, H + n + 1, l) - H;
}

int mapeiaRight(int r){
	return upper_bound(H + 1, H + n + 1, r) - H - 1;
}

struct wavelet{
	int lo, hi;
	vector<int> b;
	wavelet *left, *right;
	
	wavelet(int *from, int *to, int mn, int mx){
		lo = mn;
		hi = mx;
		if(mn == mx || from == to) return;
		
		int mid = (mn + mx) / 2;
		auto f = [mid](int i){return i <= mid;};
		
		b.pb(0);
		for(int *i = from; i != to; i++) b.pb(b.back() + f(*i));
		
		int *pivo = stable_partition(from, to, f);
		left = new wavelet(from, pivo, mn, mid);
		right = new wavelet(pivo, to, mid+1, mx);
	}
	
	int range(int l, int r, int x, int y){
		if(l > r || x > y) return 0;
		if(x <= lo && hi <= y) return r - l + 1;
		if(x > hi || y < lo) return 0;
		return left->range(b[l-1] + 1, b[r], x, y) + right->range((l-1) - b[l-1] + 1, r - b[r], x, y);
	}
};

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &A[i], &H[i]);
		coder.pb(person(A[i], H[i], i));
	}
	sort(coder.begin(), coder.end());
	for (int i = 0; i < coder.size(); i++)
	{
		A[i+1] = coder[i].A;
		H[i+1] = coder[i].H;
	}
	
	wavelet *root = new wavelet(A + 1, A + n + 1, 0, 1e9);
	
	int l, r;
	for (int i = 0; i < (int)coder.size(); i++)
	{
		l = mapeiaLeft(1);
		r = mapeiaRight(coder[i].H - 1);
		ans[coder[i].id] += root->range(l, r, 1, coder[i].A);
		
		l = mapeiaLeft(1);
		r = mapeiaRight(coder[i].H);
		ans[coder[i].id] += root->range(l, r, 1, coder[i].A - 1);
		
		l = mapeiaLeft(1);
		r = mapeiaRight(coder[i].H - 1);
		ans[coder[i].id] -= root->range(l, r, 1, coder[i].A - 1);
	}
	
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	
	
	
	return 0;
}
