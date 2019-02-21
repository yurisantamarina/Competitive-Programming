#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define pb push_back

typedef long long int ll;
int v[300010];
int cnt;
int n, k;

bool pode(int idx){
	if(idx >= n) return true;
	if(cnt + !v[idx] <= k) return true;
	return false;
}

void add(int idx){
	cnt += !v[idx];
}

void del(int idx){
	cnt -= !v[idx];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	int l=0, r=0;
	
	cnt = !v[0];
	int ansL, ansR;
	int ans = 0;
	while (r < n)
	{
		if(l > r){
			r = l;
			cnt = !v[l];
		}
		if(cnt > k){
			l++;
			continue;
		}
		if(r-l+1 > ans){
			ans = r-l+1;
			ansL = l;
			ansR = r;
		}
		if(pode(r+1)){
			add(++r);
		}else{
			del(l++);
		}
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++)
	{
		if(ansL<=i && i<=ansR) cout << "1 ";
		else cout << v[i] << " ";
	}
	cout << endl;
	
	
	

	return 0;
}
