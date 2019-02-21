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
const ll MOD = 0;
const int INF = 1e9 + 10;
const ll LINF = 1e18 + 10;
#define MAXN 100100

int read_int(){
	char r;
	bool start=false,neg=false;
	int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}


 
struct node{
	int pref, suf, total, mss;
	int lPref, rPref;
	int lSuf, rSuf;
	int lTotal, rTotal;
	int lMss, rMss;
	node(){}
	node(int x){
		mss = x;
	}
	node(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l){
		pref = a;
		suf = b;
		total = c;
		mss = d;
		lPref = e;
		rPref = f;
		lSuf = g;
		rSuf = h;
		lTotal = i;
		rTotal = j;
		lMss = k;
		rMss = l;
	}
};

int v[MAXN];
node st[4*MAXN];

node merge(node esq, node dir){
	node at;
	int l1, r1, l2, r2;
	at.pref = max(esq.pref, esq.total + dir.pref);
	if(esq.pref == esq.total + dir.pref){
		l1 = esq.lPref;
		r1 = esq.rPref;
		l2 = esq.lTotal;
		r2 = dir.rPref;
		if(r1-l1 > r2-l2){
			at.lPref = l1;
			at.rPref = r1;
		}else{
			at.lPref = l2;
			at.rPref = r2;
		}
	}else if(esq.pref > esq.total + dir.pref){
		at.lPref = esq.lPref;
		at.rPref = esq.rPref;
	}else{
		at.lPref = esq.lTotal;
		at.rPref = dir.rPref;
	}
	
	at.suf = max(dir.suf, dir.total + esq.suf);
	if(dir.suf == dir.total + esq.suf){
		l1 = dir.lSuf;
		r1 = dir.rSuf;
		l2 = esq.lSuf;
		r2 = dir.rTotal;
		if(r1-l1 > r2-l2){
			at.lSuf = l1;
			at.rSuf = r1;
		}else{
			at.lSuf = l2;
			at.rSuf = r2;
		}
	}else if(dir.suf > dir.total + esq.suf){
		at.lSuf = dir.lSuf;
		at.rSuf = dir.rSuf;
	}else{
		at.lSuf = esq.lSuf;
		at.rSuf = dir.rTotal;
	}
	
	at.total = esq.total + dir.total;
	at.lTotal = esq.lTotal;
	at.rTotal = dir.rTotal;
	
	//~ at.mss = max(esq.mss, max(dir.mss, esq.suf + dir.pref));
	at.mss = esq.mss;
	at.lMss = esq.lMss;
	at.rMss = esq.rMss;
	
	if(dir.mss > at.mss){
		//~ oioi;
		at.mss = dir.mss;
		at.lMss = dir.lMss;
		at.rMss = dir.rMss;
	}else if(dir.mss == at.mss){
		l1 = at.lMss;
		r1 = at.rMss;
		l2 = dir.lMss;
		r2 = dir.rMss;
		if(r1-l1 > r2-l2){
			at.lMss = l1;
			at.rMss = r1;
		}else{
			at.lMss = l2;
			at.rMss = r2;
		}
	}
	
	if(esq.suf + dir.pref > at.mss){
		//~ oioi;
		at.mss = esq.suf + dir.pref;
		at.lMss = esq.lSuf;
		at.rMss = dir.rPref;
	}else if(esq.suf + dir.pref == at.mss){
		l1 = at.lMss;
		r1 = at.rMss;
		l2 = esq.lSuf;
		r2 = dir.rPref;
		if(r1-l1 > r2-l2){
			at.lMss = l1;
			at.rMss = r1;
		}else{
			at.lMss = l2;
			at.rMss = r2;
		}
	}
	
	return at;
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node(v[l], v[l], v[l], v[l], l, l, l, l, l, l, l, l);
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	st[no] = merge(st[nxt], st[nxt+1]);
}

node query(int no, int l, int r, int i, int j){
	if(j<l || i>r) return node(-INF);
	if(i<=l && r<=j) return st[no];
	
	
	int nxt = 2*no, mid = (l+r)/2;
	node esq = query(nxt, l, mid, i, j);
	node dir = query(nxt+1, mid+1, r, i, j);
	node at;
	//~ cout << endl;
	//~ cout << "estou em " << l << " " << r << endl; 
	//~ cout << "esq.mss = " << esq.mss << "  dir.mss = " << dir.mss << endl;
	if(esq.mss == -INF){
		//~ cout << "esquerda invalida\n";
		at = dir;
	}else if(dir.mss == -INF){
		//~ cout << "direita invalida\n";
		at = esq;
	}else{
		
		at = merge(esq, dir);
	}
	return at;
}
 
int main ()
{
	//~ node a(1,1,1,1,0,0,0,0,0,0,0,0);
	int t;
	int n;
	int q, l, r;
	//~ ios_base::sync_with_stdio (0);
	//~ cin.tie (0);
	//~ cin >> t;
	//~ scanint(t);
	t = read_int();
	node ans;
	while (t--)
	{
		
		//~ cin >> n;
		n = read_int();
		for (int i = 0; i < n; i++)
		{
			//~ cin >> v[i];
			v[i] = read_int();
		}
		build(1, 0, n-1);
		
		//~ cin >> q;
		//~ scanint(q);
		q = read_int();
		while (q--)
		{
			//~ cin >> l >> r;
			l = read_int();
			r = read_int();
			l--;
			r--;
			ans = query(1, 0, n-1, l, r);
			//~ cout << ans.mss << " " << ans.rMss-ans.lMss+1 << "\n";
			printf("%d %d\n", ans.mss, ans.rMss-ans.lMss+1);
		}
		
		
	}
	
	return 0;
}
