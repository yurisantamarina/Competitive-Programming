#include <bits/stdc++.h>

using namespace std;
#define MAXN 601010
typedef long long int ll;
struct pv{
	ll x, y;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
	ll operator * (pv other){
		return x * other.x + y * other.y;
	}
	ll operator ^ (pv other){
		return x * other.y - y * other.x;
	}
	bool operator < (pv other) const{
		if(x != other.x) return x < other.x;
		return y < other.y;
	}
	ll nsq(){
		return (*this) * (*this);
	}
};

ll n, m, dp[MAXN];
vector<pv> ch[3], poly[3];
pv p1[MAXN], p2[MAXN];
ll sz1, sz2;
vector<pair<ll, ll> > s;

void convexHull(ll op){
	vector<pv> &v = poly[op];
	sz1 = 0; sz2 = 0;
	
	sort(v.begin(), v.end());
	
	for (ll i = 0; i < (ll)v.size(); i++)
	{
		while(sz1 > 1 && ((p1[sz1 - 1] - p1[sz1 - 2]) ^ (v[i] - p1[sz1 - 2])) >= 0)
			sz1--;
		p1[sz1++] = v[i];
		
		while(sz2 > 1 && ((p2[sz2 - 1] - p2[sz2 - 2]) ^ (v[i] - p2[sz2 - 2])) <= 0)
			sz2--;
		p2[sz2++] = v[i];
	}
	
	for (ll i = 0; i < sz2; i++)
		ch[op].push_back(p2[i]);
	
	for (ll i = sz1 - 2; i >= 1; i--)
		ch[op].push_back(p1[i]);
}

bool operator == (pair<ll, ll> a, pair<ll, ll> b){
	return a.first == b.first && a.second == b.second;
}
bool operator != (pair<ll, ll> a, pair<ll, ll> b){
	return !(a == b);
}

bool kmp(ll lenPat){
	dp[0] = 0;
	ll idx = 0;
	
	for (ll i = 1; i < (ll)s.size(); i++)
	{
		while(s[i] != s[idx] && idx > 0)
			idx = dp[idx - 1];
		if(s[i] == s[idx])
			idx++;
		dp[i] = idx;
		if(idx == lenPat)
			return true;
	}
	return false;
}

ll distPtPt(pv a, pv b){
	ll A = (a.x - b.x);
	ll B = (a.y - b.y);
	return A * A + B * B;
}

pair<ll, ll> getAngle(ll op, ll idx){
	ll sz = (ll)ch[op].size();
	pv lst = (idx == 0) ? ch[op][sz - 1] : ch[op][idx - 1];
	pv nxt = (idx == sz - 1) ? ch[op][0] : ch[op][idx + 1];
	
	pv U = (lst - ch[op][idx]);
	pv V = (nxt - ch[op][idx]);
	ll dot = U * V;
	ll flag;
	if(dot < 0) flag = -1;
	else flag = 1;
	
	ll num = dot * dot;
	ll den = U.nsq() * V.nsq();
	ll g = __gcd(num, den);
	return {(flag * num) / g, den / g};
}

bool solve(){
	if((ll)ch[1].size() != (ll)ch[2].size())
		return false;
	
	ll sz = (ll)ch[1].size(), lenPat = 0;
	for (ll i = 0; i < sz; i++)
	{
		s.push_back(getAngle(1, i));
		s.push_back({distPtPt(ch[1][i], ch[1][(i + 1) % sz]), 1});
		lenPat += 2;
	}
	s.push_back({-1, -1});
	
	pair<ll, ll> aux;
	for (ll i = 0; i < sz; i++)
	{
		aux = getAngle(2, i);
		s.push_back(aux);
		aux = {distPtPt(ch[2][i], ch[2][(i + 1) % sz]), 1};
		s.push_back(aux);
	}
	
	for (ll i = 0; i < sz; i++)
	{
		aux = getAngle(2, i);
		s.push_back(aux);
		aux = {distPtPt(ch[2][i], ch[2][(i + 1) % sz]), 1};
		s.push_back(aux);
	}
	
	return kmp(lenPat);
}

int main(){
	ll x, y;
	scanf("%lld %lld", &n, &m);
	for (ll i = 1; i <= n; i++){
		scanf("%lld %lld", &x, &y);
		poly[1].push_back(pv(x, y));
	}
	for (ll i = 1; i <= m; i++){
		scanf("%lld %lld", &x, &y);
		poly[2].push_back(pv(x, y));
	}
	
	convexHull(1);
	convexHull(2);
	
	printf("%s\n", solve() ? "YES" : "NO");
	
	return 0;
}
