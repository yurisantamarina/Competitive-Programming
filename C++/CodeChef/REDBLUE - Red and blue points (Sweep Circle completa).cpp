#include <bits/stdc++.h>

using namespace std;
#define R 0
#define B 1
#define pb push_back
#define mp make_pair
typedef long long int ll;

struct pv{
	ll x, y, type;
	pv(){}
	pv(ll a, ll b){
		x = a;
		y = b;
	}
	pv(ll a, ll b, ll c){
		x = a;
		y = b;
		type = c;
	}
	ll operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y, type);
	}
};

vector<pv> v, tmp;

bool acima(pv a){
	if(a.y == 0) return a.x > 0;
	return a.y > 0;
}


ll getQuad(pv a){
	if(a.x > 0 && a.y >= 0) return 1;
	if(a.x <= 0 && a.y > 0) return 2;
	if(a.x < 0 && a.y <= 0) return 3;
	return 4;
}

bool compare(pv a, pv b){
	ll q1 = getQuad(a);
	ll q2 = getQuad(b);
	
	if(q1 != q2) return q1 < q2;
	return (a ^ b) > 0;
}


void build(ll idx){
	vector<pv> tmp2, aci, aba;
	v.clear();
	for (ll i = 0; i < tmp.size(); i++)
		if(i != idx) tmp2.pb(tmp[i] - tmp[idx]);

	sort(tmp2.begin(), tmp2.end(), compare);

	for (ll i = 0; i < tmp2.size(); i++)
	{
		if(acima(tmp2[i])) aci.pb(tmp2[i]);
		else aba.pb(tmp2[i]);
	}

	ll i = 0, j = 0;
	while(i < aci.size() && j < aba.size()){
		if((aci[i] ^ aba[j]) <= 0) v.pb(aci[i++]);
		else v.pb(aba[j++]);
	}

	while(i < aci.size()) v.pb(aci[i++]);
	while(j < aba.size()) v.pb(aba[j++]);
}



ll sweep(){
	ll redAcima = 0, blueAbaixo = 0, redAbaixo = 0, blueAcima = 0;
	//~ cout << "sz = " << v.size() << endl;
	for (ll i = 0; i < v.size(); i++)
	{
		if(acima(v[i])){
			if(v[i].type == R) redAcima++;
			else blueAcima++;
		}else{
			if(v[i].type == R) redAbaixo++;
			else blueAbaixo++;
		}
	}
	
	ll ans = 10101010;
	ans = min(ans, blueAcima + redAbaixo);//red em cima
	ans = min(ans, redAcima + blueAbaixo);//blue em cima
	
	for (ll i = 0; i < v.size(); i++)
	{
		if(acima(v[i])){
			if(v[i].type == R){
				redAcima--;
				redAbaixo++;
			}else{
				blueAcima--;
				blueAbaixo++;
			}
		}else{
			if(v[i].type == R){
				redAcima++;
				redAbaixo--;
			}else{
				blueAcima++;
				blueAbaixo--;
			}
		}
		
		ans = min(ans, blueAcima + redAbaixo);//red em cima
		ans = min(ans, redAcima + blueAbaixo);//blue em cima
	}
	
	return ans;
}

int main(){
	ll n, m, x, y;
	ll tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n >> m;
		v.clear();
		tmp.clear();
		
		for (ll i = 0; i < n; i++)
		{
			cin >> x >> y;
			tmp.pb(pv(x, y, R));
		}
		for (ll i = 0; i < m; i++)
		{
			cin >> x >> y;
			tmp.pb(pv(x, y, B));
		}
		
		ll ans = 101010;
		for (ll i = 0; i < tmp.size(); i++)
		{
			build(i);
			ans = min(ans, sweep());
		}
		cout << ans << "\n";
	}
	
	
	
	
	return 0;
}
