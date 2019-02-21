#include <bits/stdc++.h>

using namespace std;
#define MAXN 200010
#define INF 1e9
#define LOG 18
#define pb push_back

int vet[MAXN];
int dp[MAXN];
deque<int> mnDp;

struct SPARSETABLE{
	vector<int> st[MAXN];
	int sz;
	SPARSETABLE(){}
	
	void build(int _sz){
		sz = _sz;
		for (int i = 1; i <= sz; i++){
			st[i].resize(LOG);
			st[i][0] = (1<<vet[i]);
		}
		
		for (int j = 1; j < LOG; j++)
			for (int i = 1; i + (1<<j) - 1 <= sz; i++)
				st[i][j] = st[i][j-1] | st[i + (1<<(j-1))][j-1];
	}
	
	int query(int l, int r){
		int k = 31 - __builtin_clz(r-l+1);
		return __builtin_popcount(st[l][k] | st[r - (1<<k) + 1][k]);
	}
};

int k, L, R;
SPARSETABLE spt;

void add(int val){
	while(mnDp.size() > 0 && mnDp.back() > val)
		mnDp.pop_back();
	
	mnDp.pb(val);
}

void del(int val){
	if(val == mnDp.front())
		mnDp.pop_front();
}

int get(){
	return mnDp.front();
}

bool ajustaL(int i){
	if(spt.query(L+1, i) < k) return false;
	
	while (L < i && spt.query(L+1, i) > k){
		del(dp[L]);
		L++;
	}
	
	return true;
}

bool ajustaR(int i){
	if(spt.query(R+1, i) < k) return true;
	
	while (R < i && spt.query(R+1, i) >= k){
		add(dp[R]);
		R++;
	}
	
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string s;
	
	cin >> k;
	cin >> s;
	int n = (int)s.size();
	
	for (int i = 0; i < n; i++)
	{
		vet[i+1] = s[i]-'a';
	}
	L = 0; R = 0;
	spt.build(n);
	
	dp[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		if(ajustaL(i) && ajustaR(i)){
			dp[i] = get() + 1;
		}else dp[i] = INF;
		
		cout << (dp[i] >= INF ? -1 : dp[i])  << " ";
	}
	cout << "\n";
	
	
	
	return 0;
}
