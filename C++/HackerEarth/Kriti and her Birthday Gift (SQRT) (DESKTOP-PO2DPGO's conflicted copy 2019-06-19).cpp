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
	int l, r, val, pos;
};
 
int n;
string s;
map<string, int> mapa;
int f[100010];
int block_size = 320;
int saida[100010];
struct query queries[100010];
int v[100010];
 
 
 
bool compare(const struct query &a, const struct query &b){
	if(a.l/block_size == b.l/block_size) return a.r < b.r;
	return a.l < b.l;
}
 
void add(int pos){
	int val = v[pos];
	f[val]++;
}
 
void del(int pos){
	int val = v[pos];
	f[val]--;
}
 
int main () {
	
	cin >> n;
	int idx=0;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		if(mapa.find(s)==mapa.end()) mapa[s]=idx++;
		v[i] = mapa[s];
	}
	memset(f, 0, sizeof f);
	int q, L, R;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> L >> R >> s;
		queries[i].l = L-1;
		queries[i].r = R-1;
		queries[i].val = mapa.find(s)==mapa.end() ? -1 : mapa[s];
		queries[i].pos = i;
	}
	
	sort(queries, queries+q, compare);
	
	int currL = 0, currR = 0;
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		if(queries[i].val == -1){
			saida[queries[i].pos] = 0;
			continue;
		}
		
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
		
		saida[queries[i].pos] = f[queries[i].val];
	}
	
	for (int i = 0; i < q; i++)
	{
		cout << saida[i] << "\n";
	}
	
	
	
	
	
	
	return 0;
}

