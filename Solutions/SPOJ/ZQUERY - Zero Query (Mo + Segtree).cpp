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
const ll MOD = 0;
const ll N = 0;
#define prev prevv
 
struct query{
	int l, r, id;
	query(){}
	query(int a, int b, int c){
		l = a;
		r = b;
		id = c;
	}
};
 
int st[51000*8];
int v[51000];
int acc[51000];
int leftMost[111000];
int rightMost[111000];
int prox[51000];
int prev[51000];
int ans[51000];
query queries[51000];
int block_size = 230;
int n, q;
 
bool compare(query& a, query& b){
	if(a.l/block_size == b.l/block_size) return a.r < b.r;
	return a.l < b.l;
}

void update(int no, int l, int r, int pos, int val){
	if(pos<l || pos>r) return;
	if(pos==l && l==r){
		st[no] = val;
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = max(st[nxt], st[nxt+1]);
}
 
int getMax(){
	return st[1];
}
 
void Le_E_Cria(){
	acc[0] = 51000;
	map<int, int> mapa;
	
	mapa[51000] = 0;
	prox[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		acc[i] = acc[i-1]+v[i];
		prox[i] = i;
		if(mapa.find(acc[i])!=mapa.end()){
			prox[mapa[acc[i]]] = i;
		}
		mapa[acc[i]] = i;
	}
	
	mapa.clear();
	for (int i = n; i >= 0; i--)
	{
		prev[i] = i;
		if(mapa.find(acc[i])!=mapa.end()){
			prev[mapa[acc[i]]] = i;
		}
		mapa[acc[i]] = i;
	}
}
 
int main () {
	cin >> n >> q;
	
	Le_E_Cria();
	
	//~ for (int i = 0; i <= n; i++)
	//~ {
		//~ cout << prox[i] << " ";
	//~ }
	//~ cout << endl;
	
	//~ for (int i = 0; i <= n; i++)
	//~ {
		//~ cout << prev[i] << " ";
	//~ }
	//~ cout << endl;
	
	int L, R, currL=0, currR=0;
	for (int i = 0; i < q; i++)
	{
		cin >> L >> R;
		//~ queries[i] = query(L==1 ? 0 : L, R, i);
		queries[i] = query(L-1, R, i);
	}
	sort(queries, queries+q, compare);
	memset(leftMost, -1, sizeof leftMost);
	memset(rightMost, -1, sizeof rightMost);
	
	
	for (int i = 0; i < q; i++)
	{
		L = queries[i].l;
		R = queries[i].r;
		//~ cout << L << " " << R << endl; 
		while (currR <= R)
		{
			//~ printf("Adicionando %d da posicao %d\n", acc[currR]-51000, currR);
			if(leftMost[acc[currR]] == -1){
				leftMost[acc[currR]] = rightMost[acc[currR]] = currR;
			}else{
				rightMost[acc[currR]] = currR;
			}
			update(1, 0, 111000-1, acc[currR], rightMost[acc[currR]] - leftMost[acc[currR]]);
			//~ printf("%d : left = %d   right = %d\n", acc[currR]-51000, leftMost[acc[currR]], rightMost[acc[currR]]);
			currR++;
		}
		while (currL > L)
		{
			currL--;
			if(rightMost[acc[currL]] == -1){
				leftMost[acc[currL]] = rightMost[acc[currL]] = currL;
			}else{
				leftMost[acc[currL]] = currL;
			}
			update(1, 0, 111000-1, acc[currL], rightMost[acc[currL]] - leftMost[acc[currL]]);
		}
		while (currL < L)
		{
			//~ printf("Removendo %d da posicao %d\n", acc[currL]-51000, currL);
			if(leftMost[acc[currL]] == rightMost[acc[currL]]){
				leftMost[acc[currL]] = rightMost[acc[currL]] = -1;
			}else{
				leftMost[acc[currL]] = prox[currL];
			}
			update(1, 0, 111000-1, acc[currL], rightMost[acc[currL]] - leftMost[acc[currL]]);
			//~ printf("%d : left = %d   right = %d\n", acc[currL]-51000, leftMost[acc[currL]], rightMost[acc[currL]]);
			currL++;
		}
		
		while (currR > R+1)
		{
			currR--;
			if(rightMost[acc[currR]] == leftMost[acc[currR]]){
				leftMost[acc[currR]] = rightMost[acc[currR]] = -1;
			}else{
				rightMost[acc[currR]] = prev[currR];
			}
			update(1, 0, 111000-1, acc[currR], rightMost[acc[currR]] - leftMost[acc[currR]]);
		}
		
		
		
		
		
		ans[queries[i].id] = getMax();
		//~ cout << getMax() << endl;
	}
	for (int i = 0; i < q; i++)
	{
		cout << ans[i] << "\n";
	}
	
	
	
	return 0;
}
