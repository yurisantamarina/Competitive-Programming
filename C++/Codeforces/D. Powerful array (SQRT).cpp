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

int block_size = 580;
query queries[200010];
int v[200010];
ll saida[200010];
int f[1000010];
ll sum;

bool compare(query &a, query &b){
	if(a.l / block_size == b.l / block_size) return a.r < b.r;
	return a.l > b.l;
}

void add(int pos){
	int val = v[pos];
	sum -= (ll)f[val]*f[val]*val;
	f[val]++;
	sum += (ll)f[val]*f[val]*val;
}

void del(int pos){
	int val = v[pos];
	sum -= (ll)f[val]*f[val]*val;
	f[val]--;
	sum += (ll)f[val]*f[val]*val;
}

int main(){
	//~ memset(f, 0, sizeof f);
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	int n, t;
	int a, b;
	//~ cin >> n >> t;
	scanf("%d %d", &n, &t);
	for (int i = 0; i < n; i++)
	{
		//~ cin >> v[i];
		scanf("%d", &v[i]);
	}
	//~ block_size = sqrt(n);
	for (int i = 0; i < t; i++)
	{
		//~ cin >> a >> b;
		scanf("%d %d", &a, &b);
		//~ queries[i] = query(a-1, b-1, i);
		queries[i].l = a-1;
		queries[i].r = b-1;
		queries[i].pos = i;
	}
	sort(queries, queries+t, compare);
	sum = 0LL;
	int currL=0, currR=0, L=0, R=0;
	
	
	for (int i = 0; i < t; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		//~ cout << L << " " << R << endl;
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
		saida[queries[i].pos] = sum;
	}
	
	for (int i = 0; i < t; i++)
	{
		printf("%lld\n", saida[i]);
	}
	
	
	
	
	
	
	
	
	return 0;
} 
