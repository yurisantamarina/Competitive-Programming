#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define digitCountDec(a) (int)floor(1 + log10((double)a))
#define digitCount(a, b) (int)floor(1 + log10((double)a) / log10((double)b))
using namespace std;
typedef unsigned long long int llu;
typedef long long int ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};

struct query{
	int l, r, pos;
	query(){}
	query(int a, int b, int c){
		l = a;
		r = b;
		pos = c;
	}
};

//~ map<int, int> f;
int n, q;
int block_size = 320;
vector<query> queries;
int v[100010];
int saida[100010];
int f[100010];
int cnt=0;

bool compare(query &a, query &b){
	if(a.l/block_size == b.l/block_size) return a.r < b.r;
	return a.l < b.l;
}

void add(int pos){
	int val = v[pos];
	int freq = ++f[val];
	//~ cout << freq << " ";
	if(freq == val + 1) cnt--;
	if(freq == val) cnt++;
}

void del(int pos){
	int val = v[pos];
	int freq = --f[val];
	//~ cout << freq << " ";
	if(freq == val-1) cnt--;
	if(freq == val) cnt++;
}

int main(){
	//~ cin >> n >> q;
	scanf("%d %d", &n, &q);
	int a, b;
	for (int i = 0; i < n; i++)
	{
		//~ cin >> v[i];
		scanf("%d", &v[i]);
		//~ cout << v[i] << " " ;
	}
	//~ cout << endl;
	
	for (int i = 0; i < q; i++)
	{
		//~ cin >> a >> b;
		scanf("%d %d", &a, &b);
		a--;
		b--;
		queries.pb(query(a, b, i));
	}
	
	sort(queries.begin(), queries.end(), compare);
	
	//~ int cnt=0;
	int currL=0, currR=0, L=0, R=0;
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		//~ cout << L << " " << R << endl;
		while (currL < L)
		{
			//~ printf("deletando %d ", v[currL]);
			if(v[currL]<=n) del(currL);
			//~ printf("%d\n", f[v[currL]]);
			currL++;
		}
		
		while (currR <= R)
		{
			//~ printf("adicionando %d ", v[currR]);
			if(v[currR]<=n) add(currR);
			//~ printf("%d\n", f[v[currR]]);
			currR++;
		}
		
		while (currL > L)
		{
			//~ printf("adicionando %d ", v[currL-1]);
			if(v[currL-1]<=n) add(currL-1);
			//~ printf("%d\n", f[v[currL-1]]);
			currL--;
		}
		
		while (currR > R+1)
		{
			//~ printf("deletando %d ", v[currR-1]);
			if(v[currR-1]<=n) del(currR-1);
			//~ printf("%d\n", f[v[currR-1]]);
			currR--;
		}
		
		saida[queries[i].pos] = cnt;
	
		
	}
	for (int i = 0; i < q; i++)
	{
		//~ cout << saida[i] << "\n";
		printf("%d\n", saida[i]);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
} 
