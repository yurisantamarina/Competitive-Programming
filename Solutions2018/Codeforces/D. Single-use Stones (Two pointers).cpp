#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
ll v[MAXN], w, pulo, at;

int main(){
	cin >> w >> pulo;
	for (int i = 1; i < w; i++)
		cin >> v[i];
	ll l = 1, r = 1;
	while(r <= pulo)
		at += v[r++];
	ll ans = at;
	r--;
	while (r < w)
	{
		//~ printf("l = %d  r = %d at = %d\n", l, r, at);
		ans = min(ans, at);
		l++;
		r++;
		if(r < w){
			at -= v[l-1];
			at += v[r];
		}
	}
	cout << ans << "\n";
	return 0;
}
