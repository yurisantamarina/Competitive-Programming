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
typedef pair<int, int> ii;
typedef vector< ii > vii;
int dr[] = {0 ,1,-1,0,1,-1,-1, 1};
int dc[] = {-1,0,0, 1,1, 1,-1,-1};

int v[200010];
vector<ii> block[460];
int saida[200010];
int block_size = 450;
int n, q;

int ini(int b){ return b*block_size; }
int fim(int b){ return min(ini(b+1) - 1, n-1); }

int func(int b, int val){
	vector<ii> :: iterator it = block[b].end();
	it--;
	if(it->F != val) return it->S;
	
	it = block[b].begin();
	if(it->F != val) return it->S;
	return -1;
}

int query(int l, int r, int val){
	int bl = l/block_size;
	int br = r/block_size;
	int pos;
	
	//~ cout << "bl = " << bl << "   br = " << br << endl;
	
	int ans = -1;
	for (pos = l; pos <= min(fim(bl), r); pos++)
	{
		if(v[pos]!=val) return pos;
	}
	
	for (int i = bl+1; i <= br-1; i++)
	{
		ans = func(i, val);
		if(ans != -1) return ans; 
	}
	
	
	for (pos = max(pos, ini(br)); pos <= r; pos++)
	{
		if(v[pos]!=val) return pos;
	}
	
	return -1;
}

int main () {
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		block[i/block_size].pb(mp(v[i], i));
	}
	
	for (int i = 0; i < block_size; i++)
	{
		if(block[i].size()==0) break;
		sort(block[i].begin(), block[i].end());
	}
	
	
	int l, r, val, ans;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r >> val;
		ans = query(l-1, r-1, val);
		if(ans!=-1) ans++;
		cout << ans << "\n";
	}
	
	
	
	return 0;
}
