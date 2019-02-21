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
#define MAXN 30010
#define MAXQ 200010
#define block_size 180
 
struct query{
	int l, r, pos;
	query(){}
	query(int a, int b, int c){
		l = a;
		r = b;
		pos = c;
	}
};
 
int v[MAXN];
query queries[MAXQ];
int saida[MAXQ];
int f[1000010];
int cnt=0;
 
bool compare(query &a, query &b){
	if(a.l/block_size == b.l/block_size) return a.r < b.r;
	return a.l < b.l;
}
 
void add(int pos){
	int val = v[pos];
	if(f[val] == 0) cnt++;
	f[val]++;
}
 
void del(int pos){
	int val = v[pos];
	if(f[val] == 1) cnt--;
	f[val]--;
}
 
int main(){
	int n, q;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	cin >> q;
	int a, b;
	for (int i = 0; i < q; i++)
	{
		cin >> a >> b;
		a--; b--;
		queries[i] = query(a, b, i);
	}
	sort(queries, queries+q, compare);
	
	//~ int cnt=0;
	int currL=0, currR=0, L=0, R=0;
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		
		while (currL < L)
		{
			del(currL);
			currL++;
		}
		
		while (currR <= R)
		{
			add(currR);
			currR++;
		}
		
		while (currL > L)
		{
			add(currL-1);
			currL--;
		}
		
		while (currR > R+1)
		{
			del(currR-1);
			currR--;
		}
		
		saida[queries[i].pos] = cnt;
		
	}
	
	for (int i = 0; i < q; i++)
	{
		cout << saida[i] << "\n";
	}
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
} 
 
