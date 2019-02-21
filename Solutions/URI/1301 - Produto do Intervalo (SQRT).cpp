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
#define MAXN 100010

int block[320];
int block_size;
int n, q;
int v[MAXN];

void reset(){
	for (int i = 0; i < 320; i++)
	{
		block[i] = 1;
	}
}

int ini(int b){
	return b*block_size;
}
int fim(int b){ 
	return min(((b+1)*block_size) - 1, n-1);
}

void update(int pos, int val){
	v[pos] = val;
	int b = pos/block_size;
	block[b]=1;
	for(int i=ini(b); i<=fim(b); i++) block[b]*=v[i]; 
}

int query(int l, int r){
	int bIni = l/block_size;
	int bFim = r/block_size;
	if(l==r) return v[l];
	//~ if(l==21 && r==22){
		//~ cout << bIni << " " << bFim << endl;
		//~ cout << v[21] << " " << v[22] << endl;
	//~ }
	int pos;
	int ans = 1;
	for(pos = l; pos <= min(r, fim(bIni)); pos++) ans*=v[pos];
	for(int i = bIni+1; i <= bFim-1; i++) ans*=block[i];
	for(pos = max(ini(bFim), pos); pos <= r; pos++) ans*=v[pos];
	
	return ans;
}

int main () {
	int l, r, pos, val;
	char op;
	while (cin >> n >> q)
	{
		reset();
		block_size = sqrt(n);
		//~ cout << block_size << endl;
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
			if(v[i]>0) v[i]=1;
			else if(v[i]<0) v[i]=-1;
			block[i/block_size] *= v[i];
		}
		
		for (int i = 0; i < q; i++)
		{
			cin >> op;
			if(op=='C'){
				cin >> pos >> val;
				pos--;
				if(val>0) val=1;
				else if(val<0) val = -1;
				update(pos, val);
			}else{
				cin >> l >> r;
				l--; r--;
				int ans = query(l, r);
				if(ans==0) cout << 0;
				else if(ans>0) cout << '+';
				else cout << '-';
			}
		}
		cout << '\n';
		
		
		
	}
	
	
	
	
	return 0;
}
