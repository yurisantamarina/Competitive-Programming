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
 
int n, q, block_size;
int v[100010];
int block[400];
 
void reset(){
	for (int i = 0; i <= block_size; i++)
	{
		block[i] = 1e9;
	}
}
 
int ini(int b){
	return b*block_size;
}
 
int fim(int b){
	return min((b+1)*block_size - 1, n-1);
}
 
int query(int l, int r){
	int bl = l/block_size;
	int br = r/block_size;
	int pos;
	int ans=1e9;
	for(pos = l; pos <= min(r, fim(bl)); pos++) ans = min(ans, v[pos]);
	for(int i = bl+1; i <= br-1; i++) ans = min(ans, block[i]);
	for(pos = max(pos, ini(br)); pos <= r; pos++) ans = min(ans, v[pos]);
	
	return ans;
}
 
int main () {
	cin >> n;
	int l, r;
	block_size = 400;
	reset();
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		block[i/block_size] = min(block[i/block_size], v[i]);
	}
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		cout << query(l, r) << "\n";
	}
	
	
	
	
	return 0;
}
