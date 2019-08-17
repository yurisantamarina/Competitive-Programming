//~ http://codeforces.com/gym/101889/my

#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define F first
#define S second
typedef long long int ll;

int f[MAXN], n, c, q;
set<pair<pair<int, int>, int> > s;

void update(int L, int R, int cor){
	vector<pair<pair<int, int>, int> > tmp;
	tmp.push_back({{L, R}, cor});
	
	int atL, atR;
	for(auto it = prev(s.upper_bound({{L, R}, 10000000})); it != s.end() && R >= it->F.F; it = s.erase(it)){
		atL = it->F.F; atR = it->F.S; cor = it->S; 
		f[cor] -= (atR - atL + 1);
		if(atL <= L - 1) tmp.push_back({{atL, L - 1}, cor});
		if(R + 1 <= atR) tmp.push_back({{R + 1, atR}, cor});
	}
	
	for (int i = 0; i < (int)tmp.size(); i++)
	{
		f[tmp[i].S] += (tmp[i].F.S - tmp[i].F.F + 1);
		s.insert(tmp[i]);
	}
}

int main(){
	scanf("%d %d %d", &n, &c, &q);
	
	f[1] = n;
	s.insert({{0, n - 1}, 1});
	
	int S, P, X, A, B, L, R;
	for (int i = 0; i < q; i++)
	{
		scanf("%d %d %d %d", &P, &X, &A, &B);
		S = f[P];
		L = ((ll)A + (ll)S * (ll)S) % n;
		R = ((ll)A + ll(S + B) * ll(S + B)) % n;
		if(L > R) swap(L, R);
		update(L, R, X);
	}
	
	int ans = 0;
	for (int i = 1; i <= c; i++)
		ans = max(ans, f[i]);
	
	printf("%d\n", ans);
	
	return 0;
}
