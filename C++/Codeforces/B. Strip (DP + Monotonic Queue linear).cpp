#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 100010
#define INF 100000000

int n, maxDif, minLen, ptr;
//~ multiset<int> atv, mnDp;
int v[MAXN], dp[MAXN];
deque<int> atvMn, atvMx, mnDp; 

bool pode(){
	int mn, mx;
	mn = atvMn.front();
	mx = atvMx.front();
	
	return mx - mn <= maxDif;
}

int getMin(){
	return mnDp.front();
}

void insere(int val){
	while (atvMn.size() > 0 && atvMn.back() > val)
	{
		atvMn.pop_back();
	}
	atvMn.push_back(val);
	
	while (atvMx.size() > 0 && atvMx.back() < val)
	{
		atvMx.pop_back();
	}
	atvMx.push_back(val);
}

void insereDp(int val){
	while (mnDp.size() > 0 && mnDp.back() > val)
	{
		mnDp.pop_back();
	}
	mnDp.push_back(val);
}

void apaga(int val){
	if(val == atvMn.front()) atvMn.pop_front();
	if(val == atvMx.front()) atvMx.pop_front();
}

void apagaDp(int val){
	if(val == mnDp.front()) mnDp.pop_front();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> maxDif >> minLen;
	
	for (int i = 1; i <= n; i++)
		cin >> v[i];

	for (int i = 1; i <= minLen; i++){
		insere(v[i]);
		dp[i] = INF;
	}
	
	insereDp(0);
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
			
			apaga(v[l]);
			apagaDp(dp[l-1]);
			l++;
		}
		if(ok)
			dp[r] = getMin() + 1;
		else
			dp[r] = INF;
		
		if(r == n) break;
		insere(v[r+1]);
		insereDp(dp[ptr++]);
	}
	
	if(dp[n] >= INF) cout << "-1\n";
	else cout << dp[n] << "\n";
	
	return 0;
}
