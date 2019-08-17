#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 100010
#define INF 100000000

int n, maxDif, minLen, ptr;
multiset<int> atv, mnDp;
int v[MAXN], dp[MAXN];

bool pode(){
	int mn, mx;
	mn = *atv.begin();
	mx = *(--atv.end());
	
	return mx - mn <= maxDif;
}

int getMin(){
	return *mnDp.begin();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> maxDif >> minLen;
	
	for (int i = 1; i <= n; i++)
		cin >> v[i];

	for (int i = 1; i <= minLen; i++){
		atv.insert(v[i]);
		dp[i] = INF;
	}
	
	mnDp.insert(0);
	ptr = 1;
	
	int l = 1;
	bool ok;
	
	for (int r = minLen; r <= n; r++)
	{
		ok = true;
		while(!pode()){
			if(r-l+1 == minLen){
				ok = false;
				break;
			}
			
			atv.erase(atv.find(v[l]));
			mnDp.erase(mnDp.find(dp[l-1]));
			l++;
		}
		if(ok)
			dp[r] = getMin() + 1;
		else
			dp[r] = INF;
		
		if(r == n) break;
		atv.insert(v[r+1]);
		mnDp.insert(dp[ptr++]);
	}
	
	if(dp[n] >= INF) cout << "-1\n";
	else cout << dp[n] << "\n";
	
	return 0;
}
