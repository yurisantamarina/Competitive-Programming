#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = {0 ,1,-1,0,1,-1,-1, 1};
const int dy[] = {-1,0,0, 1,1, 1,-1,-1};
#define MAXN 100010

struct query{
	int l, r, pos;
	query(){}
	query(int a, int b, int c){
		l = a;
		r = b;
		pos = c;
	}
};

int tree[MAXN];
unordered_map<int, int> mapa;
int rev[MAXN], f[MAXN];
int sz=1;
query queries[MAXN];
int v[MAXN];
int saida[MAXN];
int block_size = 320;
int mx=0;

bool compare(query &a, query &b){
	if(a.l / block_size == b.l / block_size) return a.r < b.r;
	return a.l < b.l;
}

void add(int pos){
	int val = v[pos];
	
	tree[f[val]]--;
	f[val]++;
	tree[f[val]]++;
	mx = max(mx, f[val]);
	
}

void del(int pos){
	int val = v[pos];
	
	tree[f[val]]--;
	f[val]--;
	tree[f[val]]++;
	for (int i = mx+1; i >= 0; i--)
	{
		if(tree[i] > 0){
			mx = i;
			break;
		}
	}
}

int main(){
	int n, q;
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	while (cin >> n, n!=0)
	{
		cin >> q;
		mx = 0;
		memset(tree, 0, sizeof tree);
		for (int i = 0; i < n; i++){
			cin >> v[i];
			if(mapa.find(v[i])==mapa.end()){
				mapa[v[i]] = sz;
				rev[sz++] = v[i];
			}
			v[i] = mapa[v[i]];
		}
		
		int l, r, currL=0, currR=0;
		for (int i = 0; i < q; i++)
		{
			cin >> l >> r;
			queries[i] = query(l-1, r-1, i);
		}
		
		sort(queries, queries+q, compare);
		
		for (int i = 0; i < q; i++)
		{
			l = queries[i].l;
			r = queries[i].r;
			
			while (currR <= r)
			{
				add(currR);
				currR++;
			}
			while (currL > l)
			{
				add(currL - 1);
				currL--;
			}
			while (currL < l)
			{
				del(currL);
				currL++;
			}
			while (currR > r+1)
			{
				del(currR-1);
				currR--;
			}
			//~ cout << "query = " << l+1 << " " << r+1 << endl;
			//~ for(auto i : f) cout << rev[i.F] << " = " << i.S << endl;
			
			
			//~ cout << sum(3) << endl;
			saida[queries[i].pos] = mx;
			//~ cout << endl;
		}
		for (int i = 0; i < q; i++)
		{
			cout << saida[i] << "\n";
		}
	}
	
	
}
